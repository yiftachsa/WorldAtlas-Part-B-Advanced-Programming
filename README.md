# World Atlas - Part B - Abstract data types - Advanced-Programming

This repository includes the third assignment created as part of the Advanced Programming course at the Ben-Gurion University of the Negev.

<p align="center">
<img src="https://shushan.co.il/wp-content/uploads/2021/08/bash.jpg"  width=30%>
<img src="https://wallpaperaccess.com/full/1537294.png"  width=25%>
<img src="https://i.pinimg.com/originals/fe/60/4c/fe604c386cbe5de093a44ac6584be8c4.jpg"  width=25%>
</p>

The Advanced Programming course goes over **C programming**, by focusing on **abstract data types** including the main components, **structures**, **linked lists**, **modules**, **memory management, **file handling**, and the **compilation process**... In addition, **C++ programming** principles and mechanisms like **encapsulation**, **inheritance**, **polymorphism**, **generic programming**, and **templates** were taught. The course also teaches script languages as another approach to programming.


## Generic Abstract Data Types (ADT)
Generic ADT that help us with the worldAtlas ([Part A Repository](https://github.com/yiftachsa/WorldAtlas-Part-A-Advanced-Programming)).

### What does it contain?
<ul>
  <li><ins><b>Generic LinkedList.</b></ins> Supports the following functions: create, destroy, append node, delete node, display list, search for node.</li>
  <li><ins><b>Generic KeyValuePair.</b></ins> Supports the following functions: create, destroy, displayValue, displayKey, getValue, getKey, isEqualKey.</li>
  <li><ins><b>Generic HashTable</b></ins> that contains keyValuePair. Collisions treated with chaining. Supports the following functions: create, destroy, add pair, lookup for pair, remove pair, display elements.</li>
</ul>

### How does it work?

run the following command:
```./Globe <HashNumber>< numberOfCountries><configuration>```
while "HashNumber" is the required size of the hashtable, and the other parameters are the same as the previous project.
