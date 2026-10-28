//! This contains sort of a mental model of the linux 
//! kernel I made for myself. It provides and overview
//! of the `rust/kernel/` modules and how they work togeather
//! in a breif manner.


### ACPI 
This module contains Power Interface abstractions though it only offers 
2 features as of current. 
1-> Create a new device from and ACRP `id` string.
2-> A macro export of `acpi_device_table`.

This module wraps `drivers/acpi/` in a minimal manner. 

### alloc.rs 
As the name implies this module contains the memory allocation 
infrastructure for the kernel and exposes functions such as 
`alloc`, `free`, `realloc`, `dangling_from_layout` and a lot of
consts. These exposed functions can be used with or, bitor, and.

### auxillary.rs 
It matches drivers to a virtual slice of a device that a parent 
driver chose to create. (i.e, a parent driver creates a `virtual device`)
per job and hand over control to the respective `sub-driver` for that job. 
Therefore, it matches drivers to `virtual slices` of a device that a parent 
driver chose to create. 

it exposes functions like 
- `register`
- `unregister` 
- `probe_callback`
- `remove_callback`
- `new`
- `registeration_data_with` - Access the registration data set by the registering (parent)
driver through a closure.

### bitfield.rs 
#### What is a bitfield? 
Hardware registers often cram muiltiple settings into a single number, for e.g
a 32 bit register might allocate buts 0-3 for something, 4-11 for some other thing
and so on. 

#### What does this module do?
It exposes a macro `bitfield!` through which you only need to define the layout 
once instead of manually shifting through it as in `C` and it will generate 
a Rust struct with a named accessor for each field. 

Each field is typed using `Bounded` [1] to ensure values are properly validated to
`avoid implicit data loss` [2]. 

[1]: `Bounded` is a type that holds a number guranteed to fit within a certain range
of bits. 
[2]: In `C`, if we try to write 20 to a `4-bit` filed (can only store upto 15), the extra
bits are silently chopped of without warning which results in the accessor recieving 
wrong value.
