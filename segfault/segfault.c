#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

const char* signal_name(int signum) {
    switch (signum) {
        case SIGSEGV: return "SIGSEGV (Segmentation fault)";
        case SIGFPE:  return "SIGFPE (Floating point exception)";
        case SIGILL:  return "SIGILL (Illegal instruction)";
        case SIGBUS:  return "SIGBUS (Bus error)";
        case SIGABRT: return "SIGABRT (Abort)";
        case SIGTERM: return "SIGTERM (Termination)";
        case SIGINT:  return "SIGINT (Interrupt)";
        default:      return "Unknown signal";
    }
}

void handler(int signum) {
    printf("Caught signal %d: %s\n", signum, signal_name(signum));
    exit(1);
}

void null_pointer_dereference() {
    int *ptr = NULL;
    *ptr = 42;
}

void use_after_free() {
    int *x = malloc(sizeof(int));
    free(x);
    *x = 10;
}

void stack_overflow() {
    stack_overflow();
}

void divide_by_zero() {
    volatile int zero = 0;
    int crash = 1 / zero;
    printf("This line should not be reached: %d\n", crash);
    (void)crash;
}

void illegal_instruction() {
    void (*bad_func)() = (void(*)())"\xFF\xFF\xFF\xFF";
    bad_func();  // Attempt to execute invalid instructions
}

void abort_crash() {
    abort();  // Triggers SIGABRT
}

void misaligned_access() {
    char buffer[sizeof(int) + 1];
    int *misaligned_ptr = (int *)(buffer + 1);  // Unaligned on most platforms
    *misaligned_ptr = 42;  // Crash or undefined behavior
}

void double_free() {
    int *x = malloc(sizeof(int));
    free(x);
    free(x);  // Boom!
}

void write_readonly_memory() {
    char *str = "This is a string literal";
    str[0] = 't';  // Attempt to modify read-only memory → crash
}

void invalid_free() {
    int x;
    free(&x);  // Invalid free on stack variable - should crash
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <crash_type>\n", argv[0]);
        printf("1 = Null pointer dereference\n");
        printf("2 = Use after free\n");
        printf("3 = Stack overflow\n");
        printf("4 = Division by zero\n");
        printf("5 = Illegal instruction\n");
        printf("6 = Abort crash\n");
        printf("7 = Misaligned access\n");
        printf("8 = Double free\n");
        printf("9 = Write to read-only memory\n");
        printf("10 = Invalid free\n");
        return 1;
    }

    // Register handlers for signals we want to catch
    signal(SIGSEGV, handler);
    signal(SIGFPE, handler);
    signal(SIGILL, handler);
    signal(SIGBUS, handler);
    signal(SIGABRT, handler);
    signal(SIGTERM, handler);
    signal(SIGINT, handler);

    int crash_type = atoi(argv[1]);
    switch (crash_type) {
        case 1:
            null_pointer_dereference();
            break;
        case 2:
            use_after_free();
            break;
        case 3:
            stack_overflow();
            break;
        case 4:
            divide_by_zero();
            break;
        case 5:
            illegal_instruction();
            break;
        case 6:
            abort_crash();
            break;
        case 7:
            misaligned_access();
            break;
        case 8:
            double_free();
            break;
        case 9:
            write_readonly_memory();
            break;
        case 10:
            invalid_free();
            break;
        default:
            printf("Unknown crash type.\n");
            return 1;
    }

    printf("No crash occurred.\n");
    return 0;
}
