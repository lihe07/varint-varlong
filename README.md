# varint and varlong
 C++ implementation of varint and varlong

### Demo

```c++
    unsigned int origin = 114514;
    unsigned char varint[varint_encoding_length(origin)];
    varint_encode(origin, varint);
    cout << "origin uint:" << origin << endl;
    cout << "varint size:" << sizeof(varint)  <<  endl;
    for (int i = 0; i < sizeof(varint); ++i) {
        cout << (int)varint[i] << "/" << bitset<8>(varint[i]) << " ";
    }
    cout << endl;

    cout << "decoded: " << varint_decode(varint) << endl;

    unsigned long long int lOrigin = 1919810;
    unsigned char varlong[varlong_encoding_length(lOrigin)];
    varlong_encode(lOrigin, varlong);
    cout << "origin ulong:" << lOrigin << endl;
    cout << "varlong size:" << sizeof(varlong)  <<  endl;
    for (int i = 0; i < sizeof(varlong); ++i) {
        cout << (int)varlong[i] << "/" << bitset<8>(varlong[i]) << " ";
    }
    cout << endl;

    cout << "decoded: " << varlong_decode(varlong) << endl;
```

