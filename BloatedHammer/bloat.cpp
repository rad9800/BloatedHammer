#include <tuple>            
#include <cstdio>

/*++
Routine Description:

    This function is called as a user-mode routine
    normally during the start of execution. It's job
    is to call your function to was the time of
    sandbox, by api hammering without loop...

Arguments:

    size -  The number of times you want your specific
            function to be called. Ideally not too big
            as the compiler will complain.
    Fn   -  A function capturing a size_t value. This
            will be called size times, with an increasing
            value.  (implicit template instantiation)

Comments:
    -   We're essentially unfolding the loop. This generates
        a lot of garbage code in order to evade sandbox by a
        timeout.
    -   Requires on std:c++20 and possibly /O2
    -   Size has to be smaller than 256 if compiling on clang
        https://reviews.llvm.org/rG9c9974c3ccb6468cc83f759240293538cf123fcd


Return Value:

    None.
--*/
template<size_t size, class Fn>
auto bloat(Fn fn) -> void
{
    [&] <auto... Indexes>(std::index_sequence<Indexes...>) {
        (((fn(Indexes))), ...);
    }(std::make_index_sequence<size>{});
}

/*++
Inspirations:
    - https://unit42.paloaltonetworks.com/api-hammering-malware-families/
    - https://www.joesecurity.org/blog/498839998833561473
    - https://www.joesecurity.org/blog/3660886847485093803

Downsides:
    - Bloated file size as the loops are unrolled.
    - Requires C++20 (possible with C++17 but not as clean)
--*/
auto main() -> int
{

    bloat<512>([&](size_t val) {
        // Do whatever here to waste time like printf
        // or use a bunch of Windows APIs
        auto mod = val % 4;
        switch (mod)
        {
        case 0:
            // Nested will change CFG and take more time
            bloat<256>([&](size_t val) {
                printf("Case 0 recursive.\n");
                });
        case 1:
            bloat<32>([&](size_t val) {
                printf("Case 1 recursive.\n");
                // Nested^2 is also good
                bloat<32>([&](size_t val) {
                    printf("Case 1 double recursive.\n");
                    bloat<32>([&](size_t val) {
                        printf("Case 1 triple recursive.\n");
                        });
                    });
                });
        case 2:
            bloat<256>([&](size_t val) {
                printf("Case 2 recursive.\n");
                });

        case 3:
            bloat<256>([&](size_t val) {
                printf("Case 3 recursive.\n");
                });

        default:
            break;
        }
        });
}