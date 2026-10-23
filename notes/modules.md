//! This contains notes about the in kernel `modules` macro. 

## What does the `modules` macro do? 
The `modules` macro stores the metadata about a kernel module. 
It contains fileds such as `type`, `name`, `license` and many more. 
The metadata is then emitted into the `.modinfo` section which `modpost`, 
`modprobe` and the module loader reads. 
The main job of this macro is to then generate an entry point and exit point 
via `init_module` and `cleanup_module` for loadable modules, or an `init_call` 
entry for built in ones. 

## What would you need to define manually without the `modules` macro? 
The developer would need to manually expose the function symbols, init
and cleanup methods, the `modinfo` list, static storage and `THIS_MODULE`
plumbing, as well as keep them from being optimised away.

## If `init` returns an error, what state is the kernel left in? who cleans up? 
The kernel fails to load the module however, it continues to run and is not `tainted`.
The cleanup is handelled by `drop` for the `init` method which drops all loaded values 
in reverse order. 

## How does this entry point differ from a C `module_init`? 
In `C` any +ve `int` can be reutrned as an `errno` and the module would
load anyway with a `suspiciously returned` warning whereas in `Rust` 
the module would just fail to load on a negative `int` value. 
The state lives scattered in file level consts whereas in Rust, the 
state lives in `__MOD` static.
