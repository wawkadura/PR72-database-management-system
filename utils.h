#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

enum field_types {
    TYPE_UNKNOWN,
    TYPE_PRIMARY_KEY,
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_TEXT
};

typedef enum {
    QUERY_NONE,
    QUERY_CREATE_TABLE,
    QUERY_DROP_TABLE,
    QUERY_SELECT,
    QUERY_UPDATE,
    QUERY_DELETE,
    QUERY_INSERT,
    QUERY_DROP_DB,
} query_type_t;

struct field_definition {
    std::string field_name;
    field_types field_type;
};

struct table_definition {
    int fields_count;
    std::vector<field_definition> definitions;
};

struct field_values {
    unsigned long primary_key_value;
    int int_value;
    double float_value;
    std::string text_value;
};

struct field_record {
    std::string field_name;
    field_types field_type;
    field_values field_value;
};

struct table_records {
    int fields_count;
    std::vector<field_record> fields;
};

struct insert_query {
    const char *table_name;
    std::string field_name;
    field_types field_type;
    field_values field_value;
};

struct insert_records {
    int fields_count;
    std::vector<insert_query> fields;
};

struct index_entry {
    int field_type_t ;
    std::vector<field_definition> field_type ;
};

struct index_records {
    int fields_count;
    std::vector<field_record> fields;
};

#endif