- Welcome to Code Library -

Code library is a collection of general purpose code tools, deemed usable for other applications.

Code library is not used directly, but instead used via SVN's externals feature.  You create an
appropriate host folder for the file in your repository, and configure it to pull files from here.


- General Organization -

trunk/.          - Custom libraries go here
trunk/External/. - External libraries (zlib, bzip, etc) go here
trunk/Platform/. - Platform specific libraries and implementations go here

tags/. - specifically notable revisions of code library.  When a game ships, etc.

branches/. - Asumed to be unused, but here for future expansion
