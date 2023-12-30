# C++ Snippets

## constcast

What happens if we use `const_cast` to modify a constant? Apparently there's no single answer since it's undefined behaviour ([stackoverflow](https://stackoverflow.com/a/583150), [cppreference](https://en.cppreference.com/w/cpp/language/const_cast)), but you may get lucky and have your process killed, or you may succeed which is probably a worse outcome.

Inspired by [this talk](https://youtu.be/COEv2kq_Ht8?si=duYggaKJCo4VwGrW) (CppCon 2018: James McNellis “Unwinding the Stack: Exploring How C++ Exceptions Work on Windows”)