// sudo sysctl -w kernel.core_pattern=/home/vagrant/coredump/core-%e-%s-%u-%g-%p-%t
// mkdir /home/vagrant/coredump

// bazel build //cpp_dump_test:minidumper --compilation_mode=dbg --strip=never --copt=-O3
// bazel run //cpp_dump_test:minidumper --compilation_mode=dbg --strip=never --copt=-O3 --linkopt="-fuse-ld=lld"

#include <client/linux/handler/exception_handler.h>
#include <sentry.h>

#include <iostream>
#include <pwd.h>
#include <signal.h>
#include <unistd.h>

static bool dumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
void* context, bool succeeded) {
  printf("minidump path: %s\n", descriptor.path());
  return succeeded;
}

void crash() { volatile int* a = (int*)(NULL); *a = 1; }

int handle_input(char ch, int i) {

        if( ch == '8'){
          std::cout << "kill SIGSEGV   ";
          kill(getpid(), SIGSEGV);
        }
        else if( ch == '9'){
          std::cout << "SIGSEGV   ";
          raise(SIGSEGV);
        }
        else if( ch == 'c'){
          std::cout << "    // crash  ";
              crash();
        }
        int i2 = ch - '0';
        i = i / i2;
        std::cout << "new i = " << i << "\n";
        return i;
}

int main() {
    sentry_options_t* options = sentry_options_new();
    sentry_options_set_dsn(options, "https://cb8f04b2aa1a4ce1ae42e9a6a5b88b34@o1036448.ingest.sentry.io/6169376");
    sentry_options_set_release(options, "test@2.3.12");
    sentry_options_set_database_path(options, "sentry-db");
    // sentry_options_set_debug(options, 1);
    sentry_options_set_system_crash_reporter_enabled(options, 1);
    sentry_options_set_symbolize_stacktraces(options, 1);
    sentry_init(options);
    // sentry_options_add_attachment(options, "/var/server.log");
    sentry_set_transaction("init");
     
    // sentry_capture_event(sentry_value_new_message_event(
    //     /*   level */ SENTRY_LEVEL_ERROR,
    //     /*  logger */ "custom",
    //     /* message */ "It works!"
    // ));    

    // std::string magma_root = std::getenv("MAGMA_ROOT");
    // google_breakpad::MinidumpDescriptor descriptor(magma_root + "/core_dmp");
    // google_breakpad::ExceptionHandler eh(descriptor, NULL, dumpCallback, NULL, true, -1);

    char ch;
    int i = 123;
    std::cout << "==== minidumper ====\n";

    while(true){
        std::cout << "input:";
        std::cin >> ch;
        
        if(ch == 'q')
             break;
        
        i = handle_input(ch, i);
    }
    sentry_shutdown();
    return(0);
}
