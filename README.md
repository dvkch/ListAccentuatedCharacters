ListAccentuatedCharacters
=========================

Another tiny tool! Being french usually has no real downside, but when it comes to naming files, on a remote server using an outdated version of samba for instance, old habits can become pretty ugly.

The sole goal of this utility is to go though your files, and gently tells you to rename them if there is a non-ASCII character in it.

Usage
=====

	listaccentuatedcharacters fullpath [forbidden_name_1 [forbidden_name_2 [...]]]
	
Where `forbidden_name` is just really meaning *ignored*, files and folders with this particular name will be skipped from the analysis.

Known issues
============

• A complete list of files and folder with non ASCII names is created, then the user is asked to rename them. Meaning if you have a folder with an invalid name, containing a file with an invalid name, you won't be able to rename the file because the parent folder name changed...

• When renaming a file the app suggests you a name, created by stripping every non ASCII characters from the original filename. Unfortunately you cannot type one, you only can approve or not.

• "No" is the default answer, the only way to change that is to modify it in the code, haven't set any parameter for that yet.

License
=======

Use it, love it, and drop me a mail!