
- Welcome to Code Library -

Code library is a collection of general purpose code tools, deemed usable for other applications.

Code library is not used directly, but instead used via SVN's externals feature.  You create an
appropriate host folder for the file in your repository, and configure it to pull files from here.



- Methodology -

Libraries *do not* need to be in Code Library to be useful.  Only libraries that are deemed general
purpose, and unlikely to change in a bad way by the project manager should be included in
Code Library.

This can and should include:

- File IO code
- Compression code
- File Format Loaders
- Math Libraries
- Debugging

Libraries included here should NOT use virtuals, RTTI, try/catch, and other such "C enhanced"
features that generate code.  Templates, classes, C++ casting, and such can generate the same code
as C would, so they're acceptable and encouraged.

Engine specific implementations, despite weather they're used in multiple games or not, should not
be included in Code Library.  Code Library is for general purpose new project code.

If you're building a new game based on an old one, start with that games code and specialize it
to suit your needs, in your own repository.  DON'T ISOLATE IT AND ADD IT TO CODE LIBRARY!

The only exception to the rules may be for a GUI/Menu/HUD library, as the concept of windows,
borders, and so on is pretty well defined.  However, there may be multiple implementations.  With
physics, without physics, etc.



- General Organization -

trunk/
trunk/Elements/.  - Parts that make up a larger general purpose library.  Code goes here.
trunk/Libraries/. - Specific implementions of libraries, with used Elements externally linked.
trunk/Externals/. - External libraries (zlib, bzip, etc) go here
trunk/Platforms/. - Platform specific libraries and implementations go here. Elements and Libraries.

tags/. - specifically notable revisions of code library.  When a game ships, etc.

branches/. - Asumed to be unused, but here for future expansion



- How to use SVN Externals -

Give a folder the property "svn:externals".  Edit this property, adding a list of desired targets.

FileIO/         svn://Duffalo/puffbomb/trunk/Code/Library/FileIO
Trunko/         svn://Duffalo/twisted/test2ndtrunk
Yurbo/  -r214   svn://Duffalo/puffbomb/trunk/Code/Library/Input

Once you do an update, the folders on the left will be created, contianing the contents of the
folders on the right.  DON'T FORGET TO COMMIT THIS CHANGE, else nobody else will get it.

Note, if one line is bad, all subsiquent lines will not be executed.  -r is optional, allowing you
to specify a specific revision.  Apparently using the same folder twice (two separate externals to
the same thing) causes an error too.

Also, any changes made to the contents of the folder *MUST* be committed separately, by browsing
to the respected folder (/FileIO/ for example).  Do so only with permission from project manager.



- Notes on Library creation -

Recurvise svn:externals require full paths.  Thusly, if the repository was ever moved, the
externals would need to be updated.  SVN supports symbolic links, which includes a neat hack o
Windows that will copy the contents of the symbolic link target to where you want it.  However,
this is not portable behavior.  The symlink would point to a location where the data it wants
does not exist.

Localhost/127.0.0.1 don't work, because the SVN actions are performed locally, not on the network
machine.

"../" or "/reposname/.." or any such combination don't work either.  They're simply ignored.

This is actually a known defect of subversions design.
