# BloatedHammer
API Hammering with C++20 by folding (avoiding loops)

This is a PoC to apply modern C++ techniques to compile time API Hammering.

## Why?
- Using a pre-compliation script in order to obfuscate is difficult to develop alongside.
- Having a for loop is lame
- I was interested in this technique having read the [Unit42 report](https://unit42.paloaltonetworks.com/api-hammering-malware-families/) and thought about the best way to replicate it. 


How to use
---
```
bloat<SIZE>([&](size_t val){
  // Our lambda function will capture val which is just an incrementing index value
  // Such as CreateFile or registry stuff anything to waste time
  
  bloat<SIZE>([&](size_t val){
    // You can embed like nested loops, but it'll all be unfolded
    
  });
});
```
The bigger the size, the longer it'll take to compile, and execute.



## Next Steps?
Adding an element of randomness 

References
---
https://unit42.paloaltonetworks.com/api-hammering-malware-families/

https://www.joesecurity.org/blog/498839998833561473

https://www.joesecurity.org/blog/3660886847485093803
