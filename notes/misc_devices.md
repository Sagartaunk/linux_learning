This describes the misc_devices driver the need for it and
a few questions about it as per my understanding.


## What actual problem does a misc device solve, and why would
## one need to reach for `MISC_DYNAMIC_MINOR` instead of allocating
## one's own minor/major?

If every single device required a full major of it's own it would get
difficult to manage the enormous number of `majors` which must remain collision
free. i.e Every driver must hold a unique major number.

A misc-device solves this issue via declaring an universal API for smaller
device drivers to use. i.e Devices which do not require `majors` of their own and
whose drivers would fit perfectly fine within a `minor`.

As for `MISC_DYNAMIC_MINOR` it assigns a free dynamic number to the miscellaneous
device when registered by using `misc_register()`.It saves one from managing device
numbers manually which is a lengthy and complex procedure. Thus, making it easier to
write miscellaneous drivers.


## What does `MiscDeviceRegistration<T>` actually own, and what two kernel calls
## bracket it's lifetime? What gurantees does it's `Drop` give us?

It owns a struct `miscdevice` that is registered via `misc_register()` and
deregistered via `misc_deregister()`. Also, `Drop` gurantees that deregistration
occurs only once via `misc_deregister()`.


##`open()` returns `Self::Ptr`, constrained to `ForeignOwnable + Send + Sync`.
## Where does that value live physically between the `open()` call and the next
##`ioctl()`/`release()` call on the same fd? Why dopes it need `Send + Sync` ?

Th returned pointer is stored as the private data for the fd. Also, `Send + Sync`
is required so that the thread other than the one which called `misc_register()`
can call it and also so that multiple threads are able to call it in parallel.
