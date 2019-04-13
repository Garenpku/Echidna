#include "myJVM.h"

//enum types {PUBLIC, PRIVATE, PROTECTED} t;

class CONSTANT_METATYPE{
public:
    virtual types get_instance_type(){
        return CONS_METATYPE;
    }
    virtual void* get_value(){return NULL; }
    virtual void* get_class_name(){ return NULL; }
};

class CONSTANT_utf8: public CONSTANT_METATYPE{
public:
    int length;
    char *str;
    CONSTANT_utf8(int _length, char *utf8):length(_length){
        str = utf8;
    }
    types get_instance_type() {
        return CONS_UTF8;
    }
    void* get_value(){
        return str;
    }
};

class CONSTANT_integer: public CONSTANT_METATYPE{
public:
    int value;
    CONSTANT_integer(int _value):value(_value){}
    types get_instance_type() {
        return CONS_INTEGER;
    }
    void* get_value(){return &value;}
};

class CONSTANT_float: public CONSTANT_METATYPE{
public:
    float value;
    CONSTANT_float(float _value):value(_value){}
    types get_instance_type() {
        return CONS_FLOAT;
    }
    void* get_value(){return &value;}
};

class CONSTANT_long: public CONSTANT_METATYPE{
public:
    long value;
    CONSTANT_long(long _value):value(_value){}
    virtual types get_instance_type() {
        return CONS_LONG;
    }
    void* get_value(){return &value;}
};

class CONSTANT_double: public CONSTANT_METATYPE{
public:
    double value;
    CONSTANT_double(double _value):value(_value){}
    virtual types get_instance_type() {
        return CONS_DOUBLE;
    }
    void* get_value(){return &value;}
};

class CONSTANT_class: public CONSTANT_METATYPE{
public:
    int name_index;
    CONSTANT_class(int _value):name_index(_value){}
    types get_instance_type() {
        return CONS_CLASS;
    }
    void* get_class_name(){
        return NULL;
    }
};

class CONSTANT_string: public CONSTANT_METATYPE{
public:
    int utf8_index;
    CONSTANT_string(int _value):utf8_index(_value){}
    virtual types get_instance_type() {
        return CONS_STRING;
    }
};

class CONSTANT_fieldref: public CONSTANT_METATYPE{
public:
    int class_index;
    int name_type_index;
    CONSTANT_fieldref(int _class, int _name_type):class_index(_class), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONS_FIELD;
    }
};

class CONSTANT_methodref: public CONSTANT_METATYPE{
public:
    int class_index;
    int name_type_index;
    CONSTANT_methodref(int _class, int _name_type):class_index(_class), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONS_METHOD;
    }
};

class CONSTANT_interface: public CONSTANT_METATYPE{
public:
    int class_index;
    int name_type_index;
    CONSTANT_interface(int _class, int _name_type):class_index(_class), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONS_INTERFACE;
    }
};

class CONSTANT_name_type: public CONSTANT_METATYPE{
public:
    int name_index;
    int descriptor_index;
    CONSTANT_name_type(int _name, int _descriptor):name_index(_name), descriptor_index(_descriptor){}
    virtual types get_instance_type() {
        return CONS_NAME_TYPE;
    }
};

class CONSTANT_method_handle: public CONSTANT_METATYPE{
public:
    int reference_kind;
    int reference_index;
    CONSTANT_method_handle(int _kind, int _index):reference_kind(_kind), reference_index(_index){}
    virtual types get_instance_type() {
        return CONS_METHOD_HANDLE;
    }
};

class CONSTANT_method_type: public CONSTANT_METATYPE{
public:
    int descriptor_index;
    CONSTANT_method_type(int _descriptor):descriptor_index(_descriptor){}
    virtual types get_instance_type() {
        return CONS_METHOD_TYPE;
    }
};

class CONSTANT_invoke_dynamic: public CONSTANT_METATYPE{
public:
    int bootstrap_index;
    int name_type_index;
    CONSTANT_invoke_dynamic(int _boostrap, int _name_type):bootstrap_index(_boostrap), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONSTANT_INVOKE_DYNAMIC;
    }
};

class CONSTANT_POOL{
public:
    int length;
    CONSTANT_METATYPE ** constant_pool;
    CONSTANT_POOL(int _length):length(_length){
        constant_pool = new CONSTANT_METATYPE* [length+1];
    }
};

class TABLEINFO{
    
};

class FIELDINFO{
public:
    bool ACC_PUBLIC;
    bool ACC_PRIVATE;
    bool ACC_PROTECTED;
    bool ACC_STATIC;
    bool ACC_FINAL;
    bool ACC_VOLATILE;
    bool ACC_TRANSIENT;
    bool ACC_SYNTHETIC;
    bool ACC_ENUM;
    ushort name_index;
    ushort descriptor_index;
    ushort attributes_count;
    ATTRIBUTEINFO **attributes;
    types get_permission(){
        if (ACC_PUBLIC) return PUBLIC;
        else if (ACC_PRIVATE) return PRIVATE;
        else return PROTECTED;
    }
    FIELDINFO(int access_flags, int name_index, int descriptor_index, int attributes_count){
        this->name_index = name_index;
        this->descriptor_index = descriptor_index;
        this->attributes_count = attributes_count;
        this->ACC_PUBLIC = access_flags & 1;
        this->ACC_PRIVATE = access_flags & 2;
        this->ACC_PROTECTED = access_flags & 4;
        this->ACC_STATIC = access_flags & 8;
        this->ACC_FINAL = access_flags & 0x10;
        this->ACC_VOLATILE = access_flags & 0x40;
        this->ACC_TRANSIENT = access_flags & 0x80;
        this->ACC_SYNTHETIC = access_flags & 0x1000;
        this->ACC_ENUM = access_flags & 0x4000;
#ifdef DEBUG
        if (ACC_PUBLIC)
            printf("PUBLIC\n");
        else if (ACC_PRIVATE)
            printf("PRIVATE\n");
        else if (ACC_PROTECTED)
            printf("PROTECTED\n");
#endif
    }
};

class METHODINFO: public TABLEINFO{
public:
    bool ACC_PUBLIC;
    bool ACC_PRIVATE;
    bool ACC_PROTECTED;
    bool ACC_STATIC;
    bool ACC_FINAL;
    bool ACC_SYNCHRONIZED;
    bool ACC_BRIDGE;
    bool ACC_VARARGS;
    bool ACC_NATIVE;
    bool ACC_ABSTRACT;
    bool ACC_STRICTFP;
    bool ACC_SYNTHETIC;
    ushort name_index;
    ushort descriptor_index;
    ushort attributes_count;
    ATTRIBUTEINFO **attributes;
    types get_permission(){
        if (ACC_PUBLIC) return PUBLIC;
        else if (ACC_PRIVATE) return PRIVATE;
        else return PROTECTED;
    }
    METHODINFO(int access_flags, int name_index, int descriptor_index, int attributes_count){
        this->name_index = name_index;
        this->descriptor_index = descriptor_index;
        this->attributes_count = attributes_count;
        this->ACC_PUBLIC = access_flags & 1;
        this->ACC_PRIVATE = access_flags & 2;
        this->ACC_PROTECTED = access_flags & 4;
        this->ACC_STATIC = access_flags & 8;
        this->ACC_FINAL = access_flags & 0x10;
        this->ACC_SYNCHRONIZED = access_flags & 0x20;
        this->ACC_BRIDGE = access_flags & 0x40;
        this->ACC_VARARGS = access_flags & 0x80;
        this->ACC_NATIVE = access_flags & 0x100;
        this->ACC_ABSTRACT = access_flags & 0x400;
        this->ACC_STRICTFP = access_flags & 0x800;
        this->ACC_SYNTHETIC = access_flags & 0x1000;
        this->attributes = new ATTRIBUTEINFO* [attributes_count+1];
#ifdef DEBUG
        if (ACC_PUBLIC)
            printf("PUBLIC\n");
        else if (ACC_PRIVATE)
            printf("PRIVATE\n");
        else if (ACC_PROTECTED)
            printf("PROTECTED\n");
#endif
    }
};

class ATTRIBUTEINFO{
public:
    ushort attribute_name_index;
    uint attribute_length;
    ATTRIBUTEINFO(ushort index, ushort length):attribute_name_index(index), attribute_length(length){}
    virtual void** get_attributes(){return NULL;}
};

class CODE:public ATTRIBUTEINFO{
public:
    ushort max_stack;
    ushort max_locals;
    uint code_length;
    uchar *code;
    ushort exception_table_length;
    ushort attributes_count;
    ATTRIBUTEINFO **attributes;
    EXCEPTIONINFO **exception_table;
    void** get_attributes(){ return (void**)attributes; }
    CODE(ushort ani, uint al, ushort ms, ushort ml, uint cl, uchar *cd, ushort etl, ushort ac):ATTRIBUTEINFO(ani, al), max_stack(ms), max_locals(cl), code_length(cl), exception_table_length(etl), attributes_count(ac){
        attributes = new ATTRIBUTEINFO* [ac];
        exception_table = new EXCEPTIONINFO* [etl];
        code = cd;
    }
};

class LINENUMBERINFO{
public:
    ushort start_pc;
    ushort line_number;
    LINENUMBERINFO(ushort s, ushort l):start_pc(s), line_number(l){}
};

class LINENUMBERTABLE: public ATTRIBUTEINFO{
public:
    ushort line_number_table_length;
    LINENUMBERINFO** line_number_table;
    void** get_attributes(){ return (void**)line_number_table; }
    LINENUMBERTABLE(ushort ani, uint al, ushort lntl):ATTRIBUTEINFO(ani, al), line_number_table_length(lntl){
        line_number_table = new LINENUMBERINFO* [lntl+1];
    }
};

class class_attribute{
public:
    uint magic;
    ushort minor_version;
    ushort major_version;
    ushort constant_pool_count;
    ushort access_flags;
    CONSTANT_POOL *cpool;
    ushort parent_index;
    ushort class_index;
    ushort interface_index_length;
    ushort field_count;
    ushort method_count;
    FIELDINFO **field_info;
    METHODINFO **method_info;
    bool ACC_PUBLIC;
    bool ACC_FINAL;
    bool ACC_SUPER;
    bool ACC_INTERFACE;
    bool ACC_ABSTRACT;
    bool ACC_SYNTHETIC;
    bool ACC_ANNOTATION;
    bool ACC_ENUM;
    class_attribute(char *path){
        FILE *file;
        char *buffer = new char[10000];
        int point = 0;
        memset(buffer, 0, 10000);
        file = fopen(path, "r");
        fread(buffer, 10000, 1, file);
        // magic number
        this->magic = read_u(buffer, 4, &point);
        printf("magic: %x\n", this->magic);
        
        // minor/major version
        this->minor_version = read_u(buffer, 2, &point);
        printf("minor_version: %x\n", this->minor_version);
        this->major_version = read_u(buffer, 2, &point);
        printf("major_version: %x\n", this->major_version);
        
        // constant pool length
        this->constant_pool_count = read_u(buffer, 2, &point);
        printf("constant pool len: %x\n", this->constant_pool_count);
        
        // constant pool
        this->cpool = new CONSTANT_POOL(this->constant_pool_count);
        process_constant_pool(buffer, this->constant_pool_count, &point, this->cpool);
        
        // access flags
        this->access_flags = read_u(buffer, 2, &point);
        process_access_flags(this, this->access_flags);
#ifdef DEBUG
        printf("NOW COUNT: %d\n", point);
#endif
        this->class_index = read_u(buffer, 2, &point);
        this->parent_index = read_u(buffer, 2, &point);
        this->interface_index_length = read_u(buffer, 2, &point);
#ifdef DEBUG
        printf("father index: %u\nclass index: %u\n", this->parent_index, this->class_index);
#endif
        // At this time we just ignore the interface index set.
        if (this->interface_index_length != 0){
            printf("Error: interface index length != 0!");
            exit(0);
        }
        
        // field table set
        this->field_count = read_u(buffer, 2, &point);
#ifdef DEBUG
        printf("field info count: %u\n", this->field_count);
#endif
        field_info = new FIELDINFO* [this->field_count];
        process_field_info(buffer, this->field_count, &point, this);
        
        this->method_count = read_u(buffer, 2, &point);
#ifdef DEBUG
        printf("method info count: %u\n", this->field_count);
#endif
        method_info = new METHODINFO* [this->method_count];
        process_method_info(buffer, this->method_count, &point, this);
        
        delete[] buffer;
    }
};

uint read_u(char *buffer, int count, int *point){
    char tmp[8] = {};
    uint result = 0;
    uint store = 0;
    memcpy(tmp, buffer + *point, count);
    *point += count;
    for (int i = 0; i < count; i ++){
        store = ((store | tmp[count - i - 1]) & 0xff ) << (8 * i);
        result = result | store;
        store = 0;
    }
    return result;
}

double read_f(char *buffer, int count, int *point){
    double value;
    memcpy(&value, buffer + *point, count);
    *point += count;
    return value;
}

int process_constant_pool(char *buffer, int count, int *point, CONSTANT_POOL *cpool){
    int tag;
    int cnt = 1;
    //char *tmp;
    //tmp = (char*) malloc(sizeof(char) * count + 1);
    //memcpy(tmp, buffer + *point, count);
    while (cnt < count){
        //printf("position: %d limit: %d\n", cnt, count);
        tag = read_u(buffer, 1, point);
        //printf("The tag of this constant: %x\n", tag);
        switch(tag){
                // utf-8 info
            case(1):{
                int length = read_u(buffer, 2, point);
                char *utf8 = (char*) malloc(sizeof(char) * length + 1);
                memcpy(utf8, buffer + *point, length);
                *point += length;
                CONSTANT_utf8 *tmp = new CONSTANT_utf8(length, utf8);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("The utf8 literal: %s\n", utf8);
#endif
                break;
            }
                // Integer info
            case(3):{
                int value = read_u(buffer, 4, point);
#ifdef DEBUG
                CONSTANT_integer *tmp = new CONSTANT_integer(value);
                cpool->constant_pool[cnt] = tmp;
                printf("Constant Pool %d -- ", cnt);
                printf("The integer value: %d\n", value);
#endif
                break;
            }
                // Float info
            case(4):{
                float value = read_f(buffer, 4, point);
                CONSTANT_float *tmp = new CONSTANT_float(value);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("The float value: %f\n", value);
#endif
                break;
            }
                // Long info
            case(5):{
                long value = read_u(buffer, 8, point);
                CONSTANT_long *tmp = new CONSTANT_long(value);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("The long value: %ld\n", value);
#endif
                break;
            }
                // Double info
            case(6):{
                double value = read_f(buffer, 8, point);
                CONSTANT_double *tmp = new CONSTANT_double(value);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("double value: %lf\n", value);
#endif
                break;
            }
                // Class info
            case(7):{
                int index = read_u(buffer, 2, point);
                CONSTANT_class *tmp = new CONSTANT_class(index);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class info index: %d\n", index);
#endif
                break;
            }
                // String info
            case(8):{
                int index = read_u(buffer, 2, point);
                CONSTANT_string *tmp = new CONSTANT_string(index);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("string info index: %d\n", index);
#endif
                break;
            }
                // Fieldref info
            case(9):{
                int index_class = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_fieldref *tmp = new CONSTANT_fieldref(index_class, index_name_type);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name and type index:%d\n", index_class, index_name_type);
#endif
                break;
            }
                // Methodref info
            case(10):{
                int index_class = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_methodref *tmp = new CONSTANT_methodref(index_class, index_name_type);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name index:%d\n", index_class, index_name_type);
#endif
                break;
            }
                // Interface_methodref
            case(11):{
                int index_class = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_interface *tmp = new CONSTANT_interface(index_class, index_name_type);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name index:%d\n", index_class, index_name_type);
#endif
                break;
            }
                // Name_and_type info
            case(12):{
                int index_name = read_u(buffer, 2, point);
                int index_descriptor = read_u(buffer, 2, point);
                CONSTANT_name_type *tmp = new CONSTANT_name_type(index_name, index_descriptor);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name index:%d\n", index_name, index_descriptor);
#endif
                break;
            }
                // Method_handle info
            case(15):{
                int reference_kind = read_u(buffer, 1, point);
                int index_reference = read_u(buffer, 2, point);
                CONSTANT_method_handle *tmp = new CONSTANT_method_handle(reference_kind, index_reference);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("reference kind:%d, reference index:%d\n", reference_kind, index_reference);
#endif
                break;
            }
                // Method_type info
            case(16):{
                int index_descriptor = read_u(buffer, 2, point);
                CONSTANT_method_type *tmp = new CONSTANT_method_type(index_descriptor);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("descriptor index:%d\n", index_descriptor);
#endif
                break;
            }
                // Invoke_dynamic info
            case(18):{
                int index_bootsrap = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_invoke_dynamic *tmp = new CONSTANT_invoke_dynamic(index_bootsrap, index_name_type);
                cpool->constant_pool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("bootsrap index:%d, name_type index:%d\n", index_bootsrap, index_name_type);
#endif
                break;
            }
        }
        cnt += 1;

    }
    return 0;
}

void process_access_flags(class_attribute *p, ushort flag){
    p->ACC_PUBLIC = flag & 1;
    p->ACC_FINAL = flag & 0x10;
    p->ACC_SUPER = flag & 0x20;
    p->ACC_INTERFACE = flag & 0x200;
    p->ACC_ABSTRACT = flag & 0x400;
    p->ACC_SYNTHETIC = flag & 0x1000;
    p->ACC_ANNOTATION = flag & 0x2000;
    p->ACC_ENUM = flag & 0x4000;
}

void process_field_info(char *buffer, int count, int *point, class_attribute *cl){
    ushort access_flags, name_index, descriptor_index, attributes_count;
    for (int i = 0; i < count; i ++){
        access_flags = read_u(buffer, 2, point);
        name_index = read_u(buffer, 2, point);
        descriptor_index = read_u(buffer, 2, point);
        attributes_count = read_u(buffer, 2, point);
        cl->field_info[i] = new FIELDINFO(access_flags, name_index, descriptor_index, attributes_count);
#ifdef DEBUG
        printf("New field info, name_index:%u, descriptor_index:%u, attributes:%u\n", name_index, descriptor_index, attributes_count);
#endif
    }
}

void process_method_info(char *buffer, int count, int *point, class_attribute *cl){
    ushort access_flags, name_index, descriptor_index, attributes_count;
    for (int i = 0; i < count; i ++){
        access_flags = read_u(buffer, 2, point);
        name_index = read_u(buffer, 2, point);
        descriptor_index = read_u(buffer, 2, point);
        attributes_count = read_u(buffer, 2, point);
        cl->method_info[i] = new METHODINFO(access_flags, name_index, descriptor_index, attributes_count);
#ifdef DEBUG
        printf("New method info, name_index:%u, descriptor_index:%u, attributes:%u\n", name_index, descriptor_index, attributes_count);
#endif
        process_attribute_info(buffer, attributes_count, point, cl->method_info[i]->attributes, cl);
    }
}

void process_attribute_info(char *buffer, int count, int *point, ATTRIBUTEINFO **attr, class_attribute *cl){
    for (int i = 0; i < count; i ++){
        ushort index = read_u(buffer, 2, point);
        uint length = read_u(buffer, 4, point);
#ifdef DEBUG
        printf("Pointer here: %d\n", *point);
        printf("Length of this attribute: %d\n", length);
#endif
        if (cl->cpool->constant_pool[index]->get_instance_type() != CONS_UTF8)
            exit(0);
        char *str = (char*) cl->cpool->constant_pool[index]->get_value();
#ifdef DEBUG
        printf("Attribute %d, index: %d, name: %s\n", i+1, index, str);
#endif
        if (!strcmp(str, "Code")){
            ushort max_stack = read_u(buffer, 2, point);
            ushort max_locals = read_u(buffer, 2, point);
            uint code_length = read_u(buffer, 4, point);
#ifdef DEBUG
            printf("In code: %d bytes\n", code_length);
#endif
            uchar *code = new uchar [code_length+1];
            memcpy(code, buffer+(*point), code_length);
            *point += code_length;
            ushort exception_table_length = read_u(buffer, 2, point);
            // Not handled yet
            *point += exception_table_length;
            ushort attributes_count = read_u(buffer, 2, point);
            attr[i] = new CODE(index, length, max_stack, max_locals, code_length, code, exception_table_length, attributes_count);
#ifdef DEBUG
            printf("In code: %d exceptions, %d attributes\n", exception_table_length, attributes_count);
#endif
            void **tmp = attr[i]->get_attributes();
            process_attribute_info(buffer, attributes_count, point, (ATTRIBUTEINFO**)tmp, cl);

        }
        else if (!strcmp(str, "LineNumberTable")){
            ushort line_number_table_length = read_u(buffer, count, point);
            attr[i] = new LINENUMBERTABLE(index, length, line_number_table_length);
            LINENUMBERINFO **tmp = (LINENUMBERINFO**)attr[i]->get_attributes();
            for (int j = 0; j < line_number_table_length; j ++){
                ushort start_pc = read_u(buffer, 2, point);
                ushort line_number = read_u(buffer, 2, point);
                tmp[j] = new LINENUMBERINFO(start_pc, line_number);
            }
#ifdef DEBUG
            printf("In LineNumberTable: %d tables\n", line_number_table_length);
            printf("Pointer here: %d\n", *point);
#endif
        }
        else
            *point += length;
        //*point += length;
    }
}

int main(int argc, char **argv){
    class_attribute class_file(argv[1]);
    return 0;
}
