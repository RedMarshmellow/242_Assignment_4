███████╗ ██████╗ ███╗   ███╗██████╗ ██╗███████╗    ██████╗ ██╗   ██╗███████╗████████╗███████╗██████╗ ███████╗
╚══███╔╝██╔═══██╗████╗ ████║██╔══██╗██║██╔════╝    ██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔════╝██╔══██╗██╔════╝
  ███╔╝ ██║   ██║██╔████╔██║██████╔╝██║█████╗      ██████╔╝██║   ██║███████╗   ██║   █████╗  ██████╔╝███████╗
 ███╔╝  ██║   ██║██║╚██╔╝██║██╔══██╗██║██╔══╝      ██╔══██╗██║   ██║╚════██║   ██║   ██╔══╝  ██╔══██╗╚════██║
███████╗╚██████╔╝██║ ╚═╝ ██║██████╔╝██║███████╗    ██████╔╝╚██████╔╝███████║   ██║   ███████╗██║  ██║███████║
╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚═╝╚══════╝    ╚═════╝  ╚═════╝ ╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝


by:
    Adam Mohamed I. K. - 2350775
    Ahmed H. A. A. Mohamed - 2351724

### IDE / COMPILER ###
This program was built using GCC 9.3.0 on CLion 2021.1

### CHANGES DONE TO PROJECT SETTINGS ###
No changes were made in CLion for the project settings

### TESTED PLATFORMS ###
This program was tested on Ubuntu 20.04 LTS and Windows 10(WSL 2)

### KNOWN BUGS ###
The only bug found was due to simple usage of std::cin>> to take input, giving an invalid type of input (char instead of int) would break the application.
In the interest of simplicity and focusing on the scope of the assignment we have chosen to ignore this bug.

### DEMO SESSION PREFERRED DATES ###
Adam Mohamed I. K.:
    All times are in TRNC time
    8th of July: from after exam until 9 pm
    9th of July: from 2 pm onwards
    From there onwards: due to summer internship I cannot be certain when would be appropriate, but I do not expect a large workload from the internship
Ahmed H. A. A. Mohamed:
    Any date after the final exam is manageable for me


### IMPLEMENTATION ###
Some design choices taken were as follows:
    -Players can overheal if they pick up a medkit (medkit acts a boost to their HP, like a shot of adrenaline)
    -Players will be eliminated from the game if they are surrounded by previously visited tiles and thus cannot move
    -Derick can choose to use the knife even if he has ammo
