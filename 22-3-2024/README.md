#22-03-2024
#Topic: Linux Kernel Debugging Tools  &  Patch create and apply
---
#Fetching Tools
***ctags***
	* It is a tool which is used to fetch and generate tag files for source code.

***cscope***
	* It is a tool which is used to fetch the c symbols, global definitions, functions called by this function, functions calling this function, text string, pattern , file, #include headers and assignment to the symble.
	* It provides the menu view to do fetch the parameters.
	
***indent***
	* It is API , which is used to apply the indentation to the source file, and beautifies the lines in the source code.
	$ indent -linux source.c

#Tools
				Tools
                                 / \
				/   \
			       /     \
                              /       \
                Static Analysis       Dynamic Analysis
 
***Static Analysers***
	The static analysers are tools at which checks the source files before run and execute.
 * Some tools under static analysis
	* lint  (It is a old analyser tool in UNIX)
	* coverity
	* flawfinder
	* cppcheck
	* SonarCloud
	* https://en.wikipedia.org/wiki/Static_program_analysis (Note: here you can find more static analysers)

***Dynamic Analysers***
	The dynamic analysers are tools at which checks the traces the processes at run time.
 * Some tools under dynamic analysis
	* strace    -> secure trace
	* ltrace    -> Library trace
	* https://en.wikipedia.org/wiki/Dynamic_program_analysis (Note: here you can find more dynamic analysers) 

#Creating and applying patches
***Create Patch***
	* diff -u <old file> <new file>  >  <file_name>.patch
		Ex: diff -u old.c new.c > change.patch

***Apply Patch***
	* patch -p<n> [--dry-run]  <  <file_name>.patch
		The [--dry-run] is the pre-run to avoid bugs, it is run inRAM, But dont apply to source code.

Note: $  meld -->  Visual diff and merge tool for the GNOME Desktop


