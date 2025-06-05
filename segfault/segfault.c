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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <crash_type>\n", argv[0]);
        printf("1 = Null pointer dereference\n");
        printf("2 = Use after free\n");
        printf("3 = Stack overflow\n");
        printf("4 = Division by zero\n");
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
        default:
            printf("Unknown crash type.\n");
            return 1;
    }

    printf("No crash occurred.\n");
    return 0;
}
