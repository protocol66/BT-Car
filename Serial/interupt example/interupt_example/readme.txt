//------------------------------------------------------------------------
//  Readme.txt
//------------------------------------------------------------------------
This project stationery is designed to get you up and running
quickly with CodeWarrior for MC9S12DP256B.
It is set up for the selected CPU and target connection,
but can be easily modified.

Sample code for the following language(s) is at your disposal:
- C

The wizard has prepared CodeWarrior target(s) with the connection methods of
your choice:
Simulator:
  This interface/target is prepared to use the FCS (Full Chip Simulation).


Additional connections can be chosen in the simulator/debugger,
use the menu Component > Set Target.

//------------------------------------------------------------------------
//  Processor Expert
//------------------------------------------------------------------------
This project is prepared to be designed with Processor Expert.
The project has an additional 'tab' named 'Processor Expert' where you
can configure the CPU and its beans.
The CPU selected is inserted into the Processor Expert project panel, in
the Debug and Release configurations.
Change of the configuration is possible by the mouse double-click on it.
All the installed Embedded Beans are accessible in the Bean Selector
window, grouped into folders according to their function. The mouse
double-click on selected Embedded Bean in the Bean Selector window adds
the Bean to the project. The mouse double-click on the Bean icon in the
Project panel opens the Bean Inspector window, which is used to set the
Bean properties. Source code is generated after selecting the
(Code Design 'Project_name.mcp') menu command from the CodeWarrior main
window (Processor Expert > Code design 'Project_name.mcp').
Use the bean methods and events to write your code in the main module
'Project_name'.c and the event module Events.c.

For more help please read Processor Expert help:
 (Processor Expert > Help > 'Topic').

The following folders are used in CodeWarrior project window for
ProcessorExpert:
- User modules: contains your sources. The main module 'Project_name'.c
  and event module Events.c are located here after the Processor Expert
  code generation.
- Prm: Linker parameter file used for linking. Note that the file used
  for the linker is specified in the Linker Preference Panel. To open
  the Preference Panel, please press <ALT-F7> or open the
  (Edit > 'Current Build Target Name' Settings...) menu item in the
  CodeWarrior main window menu, while the project window is opened).
  After Processor Expert code generation 'Project_name'.prm file
  will be placed here. You can switch off the .prm file generation in
  Processor Expert if you want (in the CPU bean, Build Options)
- Generated code: this folder appears after the Processor Expert code
  generation and contains generated code from Processor Expert.
- Doc: other files generated from the Processor Expert (documentation)

//------------------------------------------------------------------------
//  Getting Started
//------------------------------------------------------------------------
To build/debug your project, use the menu Project > Debug or press F5.
This will open the simulator/debugger.
Press again F5 in the debugger (or menu Run > Start/Continue) to start
the application. The menu Run > Halt or F6 stops the application.
In the debugger menu Component > Open you can load additional components.

//------------------------------------------------------------------------
// Project structure
//------------------------------------------------------------------------
The project generated contains various files/folders:
- readme.txt: this file
- Sources: folder with the application source code
- Startup Code: C/C++ startup code
- Prm:
   - burner.bbl file to generate S-Records
- Linker Map: the .map file generated by the linker
- Libraries: needed library files (ANSI, derivative header/implementation files)
- Debugger Project File: contains a .ini file for the debugger for each
  connection
- Debugger Cmd Files: contains sub-folders for each connection with command
  files

//------------------------------------------------------------------------
//  Adding your own code
//------------------------------------------------------------------------
Once everything is working as expected, you can begin adding your own code
to the project. Keep in mind that we provide this as an example of how to
get up and running quickly with CodeWarrior. There are certainly other
ways to handle interrupts and set up your linker command file. Feel free
to modify any of the source files provided.

//------------------------------------------------------------------------
//  Simulator/Debugger: Additional components
//------------------------------------------------------------------------
In the simulator/debugger, you can load additional components. Try the menu
Component > Open.

//------------------------------------------------------------------------
//  Additional documentation
//------------------------------------------------------------------------
Check out the online documentation provided. Use in CodeWarrior IDE the
menu Help > Online Manuals.

//------------------------------------------------------------------------
//  Contacting Metrowerks
//------------------------------------------------------------------------
For bug reports, technical questions, and suggestions, please use the
forms installed in the Release_Notes folder and send them to:
USA:          support@metrowerks.com
EUROPE:       support_europe@metrowerks.com
ASIA/PACIFIC: j-emb-sup@metrowerks.com