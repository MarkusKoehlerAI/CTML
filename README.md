# CTML

CTML is a C++ HTML document constructor, that was designed to be simple to use and implement.
Has no dependencies on any other projects, only the C++ standard library.

## About Version 1.0.0

This version of CTML is a complete rewrite of the library, with the API of this version being incompatible with the last.
As of now, all commits to this version are being done in a seperate `v1` branch.
Additionally, all commits will be tagged with a `1.0.0` tag, to signify that this is the first real version.

###### Why 1.0.0?

Though, the first official released version was the one currently in `master`, I feel it is out of date and cluttered.
The version in `master` is clunky, hard to maintain, and overall a nightmare in my mind.
Also, that version was never actually properly versioned, and thus there was never an actual `1.0.0`.
With that, this will be, in my mind, the first real release of CTML.

## Type of Library

Previously, CTML was a header-only library.
This was fine when the library was tiny and didn't have much complexity.
But, in thinking of the future of the library, I've decided to ditch that effort.

While, header-only is much easier to include and use, there are a number of factors that make me want to get away from that.

###### Compile Times

In adding more features, new files and code of course, have to be added.
This, in turn, requires higher compile times overall when writing your project as you have to also recompile the library.

With a single compiled library, you only have to link to it.
Thus, making compile times faster.
Think a Raspberry Pi, or similar, it would take an astronomical amount of time to compile for a platform such as that each modification of your project.

###### Organization

One of the big problems with a header-only library is the organization.
All of your code gets stuck into one monolithic file, which makes it harder to read, and harder to maintain as a result, in my mind.

###### Include Cleanliness

In a header-only library, your includes get cluttered by things you may not need.
As an example, NodeLists contain optional selector support, maybe you don't need to use a selector.
But, in a header-only library, the selector code is also included and compiled.
Instead of having that, I'd rather keep the project using the library clean.

###### Templateless

A header-only library makes sense when using a lot of templates, which are only able to be written in header files.
This library does not use templates, as it does not have a need to.

You may think that, having a non header-only library is complicated to include and use, and I do feel your pain.
But, for this project, I will keep up-to-date information on including and compiling the library on a number of platforms (at the very least, Linux and Windows with Visual Studio).

I feel as if this change, while straying away from one of the mainstays of the library, will be a beneficial one in the long run.

## Concepts

CTML 1.0.0 brings a couple of concepts to the table, in effort to improve the library.

###### Node Lists

For each node in CTML 1.0.0+, children will be represented with a new `NodeList` class.
Previously, all child nodes were represented by a `std::vector` that took `Node`.
This `NodeList` class, while being similar to a `std::vector`, will contain methods specific to interacting with HTML nodes.

As an example, for iteration through a `NodeList`, there will be a `ForEach` method, used like the below code.

    NodeList.ForEach([] (size_t index, Node node) {
        if (!node.HasClass("button"))
            return;

        node.SetAttribute("style", "background-color: red;");
    });

This method allows for a cleaner style of iteration through a collection of `Node` classes.
But, that is not the only thing that the `NodeList` will contain.
To introduce what this new container will support, the next concept will be introduced.

###### Selector Support

Pre-1.0.0 CTML supported selectors when instantiating a `Node`, but not for traversing `Node` instances.
Additionally, the selectors supported were relatively barebones, only supporting tag name, classes, and one ID.
To expand on selectors and use them more efficiently, a Selector parser will be introduced.

The selector parser will take in a selector string, and of course parse it, creating a parse tree for the selector.
This parse tree can then be used to grab `Node` instances from a `NodeList`, or to create a new `Node`.
An example of using the parse tree for a selector is shown below (not final code).

    SelectorNode selector = SelectorParser::Parse("a.button span.bold");
    NodeList     nodes    = NodeList.Select(selector);

After the `Select` method runs, it returns a `NodeList` containing each node that was found in the search.
Be careful though, the `Select` method only runs relative to the `Node` instances within, so if you want to search a document, search from the root.
As stated earlier, you would also be able to use the selector parse tree to create `Node` instances.
This is demonstrated below.

    SelectorNode selector = SelectorParser::Parse("a.button span.bold");
    Node         button(selector);

This would then create a Node that, when given as a string, looks like the following.

    <a class="button">
        <span class="bold">
        </span>
    </a>

This new selector support is more powerful, and, when used correctly, should allow for time to be cut down when writing code using CTML.


###### New Node Representation

`Node` instances previously contained a `m_type` parameter, used to determine how the `Node` should be interpreted.
While, this works for a limited amount of `Node` instances, this breaks down upon having custom `Node` representations, among other things.
I have decided that, to allow for new `Node` types in an efficient way, and without cluttering the main `Node` class with edge cases, `Node` will be easier to extend from.
The primary `Node` class will be used for most purposes, including as a root container.
But for something such as a document type, a `DocumentTypeNode` would be used, which inherits from `Node`, and contains the usual `ToString`, and other methods.

Though, since some nodes in HTML do not allow for say, class attributes, or content, `Node` will contain a few protected boolean flags, so when you inherit, you can set them.
For example, the flags for a `DocumentTypeNode` may look like the code below.

    bool m_allowChildren   = false;
    bool m_allowAttributes = false;
    bool m_closeTag        = false;

And so on, and so forth.

## Tracker for Current Version

Currently, to track my progress on this version (and hopefully other subsequent versions), I use Trello.
I've only used Trello privately, and I like it a lot.
You can find the board [right here](https://trello.com/b/NvpPLQ6w/ctml).

## Backwards Compatibility

As, most of these changes require new classes, as well as entire rewrites, there is no backwards compatibility with pre-1.0.0.
Keep that in mind when considering to upgrade to 1.0.0.

## License

The license for CTML is the same as before, MIT License.