# pClass Core 
class pClass {
     UBoolean is_loaded;
public:
     VirtualTable* vtp;
     StaticMethodTable* smtp; // 针对类中所有的静态函数的Table
 
     pClass* pFatherClass;
     MethodEntry** arrMethod; // 类中所有函数的对应MethodEntry*
     FieldEntry** arrField;
     ConstantPool* pcp;
     cvoid* GetConstantPoolItem(int pl_index) {return NULL;}
 
     bool ACC_PUBLIC;
     bool ACC_FINAL;
     bool ACC_SUPER;
     bool ACC_INTERFACE;
     bool ACC_ABSTRACT;
     bool ACC_SYNTHETIC;
     bool ACC_ANNOTATION;
     bool ACC_ENUM;
 
     UInt magic;
     UShort minor_version;
     UShort major_version;
     UShort this_class;
     UShort constant_pool_count;
 
     UShort field_count;
     UShort method_count;
 
     pClass() {}
     pClass(class_file* pcf);

# ClassLoader

namespace ClassLoader {
     map<string, int> nameMap;

     const int MAX_LOADED_CLASSNUM = 1000;
     pClass* arrLoadedClass[MAX_LOADED_CLASSNUM];

     int LoadClass(class_attribute*);
     pClass* findLoadedClass(string class_name);
}

