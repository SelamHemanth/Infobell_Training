# Kernel Build
---

***Kenel Configuration***
---

 * init/Kconfig - defines the 'General Setup' menu items!. Write the below code in Kconfig file.

---
 config HEMANTH
        bool "Hai Hemanth , This is your config button"
        default n
        help
        Turns on the hook that will cause this kernel to ...
        blah blah blah
---

**Note**: Make sure duplicate the backup file. 

***Kernel Testing***
---

 * **kbuild Test Robot**  -> It is a automatic test tool for kernel, It is developed by Intel. 
 *
