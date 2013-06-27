XnaMathWrapper
==============

A simple C++ wrapper library for Microsoft's XNAMath library (included in DirectX SDK).

__ This is a library for DirectX 9. For DirectX 11 check out DominikGrabiec/DirectXMathWrapper __ 

I have created this library as part of my current game and engine project (which I am doing just for fun and experimentation) to wrap the XNAMath functions (and previously the D3D9X libraries math functions) in a more usable C++ form.

This library is not as efficient as using the XNAMath functions directly, but it does add a nice level of expressiveness as I believe is shown in the intersection testing code (Intersect.cpp).

The code convention that I have used is pretty simple:
* 4 tab indentation, keeping the tabs.
* Use of C++11 code, including the STL where appropriate.
* UpperCamelCase for namespaces, classes, and types.
* under_score for functions and public variables.
* UPPERCASE for constants.
* Anything goes for private members.

The code that I have written myself (i.e. not the STL or the XNAMath library) I declare to be public domain, and hence it receives no warranty of any kind from me.
Please enjoy it, learn from it, and improve it if so desired.