#include <iostream>

#include "constcast/constcast.hpp"

// This doesn't work, namely the CPU will generate a page fault
// and macOS will respond to it by generating a mach exception
// with type EXC_BAD_ACCESS (which indicates that memory could not be accessed)
// and code 2, i.e. KERN_PROTECTION_FAILURE (which indicates that access was not
// permitted).
//
// Exception types are defined here
// https://opensource.apple.com/source/xnu/xnu-2050.24.15/osfmk/mach/exception_types.h.auto.html
// Codes are defined here
// https://opensource.apple.com/source/xnu/xnu-2050.24.15/osfmk/mach/kern_return.h.auto.html
//
// So what seems to happen is that the value of the constant is
// in a page that's not writable by the process.
//
// "mach exceptions" seem to be a mechanism analogous to Windows's
// structured exceptions. You can register a mach exception handler
// to handle such faults gracefully, and if no exception handler is
// found the OS translates the exception into a signal. The logic for this
// seems to be in exception_triage here
// https://opensource.apple.com/source/xnu/xnu-2050.24.15/osfmk/kern/exception.c.auto.html.
//
// This
// https://docs.darlinghq.org/internals/macos-specifics/mach-exceptions.html is
// a great overview from which I basically lifted the above paragraph.
//
// This would explain why the program just crashes with SIGBUS when ran
// without the debugger while running with the debugger produces EXC_BAD_ACCESS
// with code 2: apparently the debugger registers an exception handler.
void breakStaticConst() {
  const int &zero = constants::kZero;
  std::cout << "kZero = " << constants::kZero << std::endl;
  std::cout << "zero = " << zero << std::endl;
  const_cast<int &>(zero) = 1;
  std::cout << "kZero = " << constants::kZero << std::endl;
  std::cout << "zero = " << zero << std::endl;
}

// Somehow this works.
void breakConst() {
  const int &zero = 0;
  std::cout << "zero = " << zero << std::endl;
  const_cast<int &>(zero) = 1;
  std::cout << "zero = " << zero << std::endl;
}

int main() {
  breakStaticConst();
  return 0;
}