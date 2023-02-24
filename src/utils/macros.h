#pragma once

#define CONCAT2_(NAME1, NAME2) NAME1##NAME2
#define CONCAT2(NAME1, NAME2) CONCAT2_(NAME1, NAME2)
#define CONCAT3(NAME1, NAME2, NAME3) CONCAT2(CONCAT2(NAME1, NAME2), NAME3)
#define CONCAT4(NAME1, NAME2, NAME3, NAME4) CONCAT2(CONCAT3(NAME1, NAME2, NAME3), NAME4)
#define CONCAT5(NAME1, NAME2, NAME3, NAME4, NAME5) CONCAT4(CONCAT2(NAME1, NAME2), NAME3, NAME4, NAME5)
#define CONCAT6(NAME1, NAME2, NAME3, NAME4, NAME5, NAME6) CONCAT5(CONCAT2(NAME1, NAME2), NAME3, NAME4, NAME5, NAME6)
#define CONCAT7(NAME1, NAME2, NAME3, NAME4, NAME5, NAME6, NAME7) CONCAT6(CONCAT2(NAME1, NAME2), NAME3, NAME4, NAME5, NAME6, NAME7)

#define STRINGIFY_(VALUE) #VALUE
#define STRINGIFY(VALUE) STRINGIFY_(VALUE)

#define NAMESPACE(NAMESPACE_NAME, NAME) CONCAT3(NAMESPACE_NAME, __, NAME)
#define TYPE_METHOD(TYPE, METHOD) CONCAT3(TYPE, __, METHOD)
#define TYPE_MEMBER(TYPE, MEMBER) CONCAT3(TYPE, __, MEMBER)
#define FUNCTION_FOR_TYPE(FUNCTION, TYPE) CONCAT3(FUNCTION, __, TYPE)

#define NOT_NULL(NAME) CONCAT3(not_null, __, NAME)

// interfaces' macro helpers definitions
#define TYPE_DYNAMIC_METHOD(TYPE, METHOD) CONCAT5(TYPE, __, dynamic, __, METHOD)

#define INTERFACE_TYPE(INTERFACE_NAME) CONCAT3(INTERFACE_NAME, __, interface)
#define INTERFACE_VARIABLE(INTERFACE_NAME) CONCAT3(INTERFACE_NAME, _, interface)

#define INTERFACE_VTABLE_TYPE(INTERFACE_NAME) CONCAT3(INTERFACE_NAME, __, virtual_table)
#define INTERFACE_VTABLE_VARIABLE(INTERFACE_NAME) CONCAT3(INTERFACE_NAME, _, virtual_table)

#define INTERFACE_GETTER(TYPE_NAME, INTERFACE_NAME) TYPE_METHOD(TYPE_NAME, CONCAT3(get, _, INTERFACE_VARIABLE(INTERFACE_NAME)))
#define INTERFACE_METHOD_GETTER(INTERFACE_NAME, INTERFACE_METHOD, INTERFACE_VARIABLE) (INTERFACE_VARIABLE).INTERFACE_VTABLE_VARIABLE(INTERFACE_NAME)->INTERFACE_METHOD

// interfaces' macro boilerplates
#define DEFINE_INTERFACE_VTABLE_ADAPTER(INTERFACE_NAME)\
struct INTERFACE_VTABLE_TYPE(INTERFACE_NAME) const*/*const*/ INTERFACE_VTABLE_VARIABLE(INTERFACE_NAME)

#define DEFINE_INTERFACE_ADAPTER(INTERFACE_NAME)\
struct INTERFACE_TYPE(INTERFACE_NAME)/*const*/ INTERFACE_VARIABLE(INTERFACE_NAME)

#define DEFINE_INTERFACE_TYPE_DYNAMIC_DISPOSE_METHODS(INTERFACE_NAME)\
inline static void* TYPE_DYNAMIC_METHOD(INTERFACE_TYPE(INTERFACE_NAME), destroy_at)(struct INTERFACE_TYPE(INTERFACE_NAME)* const interface) {\
    return interface->INTERFACE_VTABLE_VARIABLE(INTERFACE_NAME)->destroy_at(interface);\
}

/*
* Inteface macros usage example:
* on_click_interface.h
* * #pragma once
* * #include "utils/macros.h"
* *
* * struct INTERFACE_TYPE(OnClick);
* * 
* * struct INTERFACE_VTABLE_TYPE(OnClick) {
* *     void (*click)(struct INTERFACE_TYPE(OnClick)* const this);
* *     void* (*destroy_at)(struct INTERFACE_TYPE(OnClick)* const this);
* * };
* * 
* * struct INTERFACE_TYPE(OnClick) {
* *     DEFINE_INTERFACE_VTABLE_ADAPTER(OnClick);
* * };
* * 
* * struct INTERFACE_TYPE(OnClick)* TYPE_METHOD(INTERFACE_TYPE(OnClick), construct_at)(struct INTERFACE_TYPE(OnClick)* const this);
* * void* TYPE_MEMBER(INTERFACE_TYPE(OnClick), destroy_at)(struct INTERFACE_TYPE(OnClick)* const this);
* * 
* * inline static void TYPE_DYNAMIC_METHOD(INTERFACE_TYPE(OnClick), click)(struct INTERFACE_TYPE(OnClick)* const this) {
* *     this->INTERFACE_VTABLE_VARIABLE(OnClick)->click(this);
* * }
* * 
* * DEFINE_INTERFACE_TYPE_DYNAMIC_DISPOSE_METHODS(OnClick);
* *
* on_click_interface.c
* * #include "on_click_interface.h"
* *
* * #include <stddef.h>
* * #include <stdlib.h>
* * #include <stdio.h>
* * 
* * void* TYPE_MEMBER(INTERFACE_TYPE(OnClick), destroy_at)(struct INTERFACE_TYPE(OnClick)* const this) {
* *     // method body
* *     // ...
* *     // boilerplate
* *     return this;
* * }
* * 
* * static struct INTERFACE_VTABLE_TYPE(OnClick) TYPE_MEMBER(INTERFACE_TYPE(OnClick), INTERFACE_VTABLE_VARIABLE(OnClick)) = {
* *     .click = NULL,
* *     .destroy_at = TYPE_MEMBER(INTERFACE_TYPE(OnClick), destroy_at)
* * };
* * 
* * struct INTERFACE_TYPE(OnClick)* TYPE_METHOD(INTERFACE_TYPE(OnClick), construct_at)(struct INTERFACE_TYPE(OnClick)* const this) {
* *     // boilerplate
* *     this->INTERFACE_VTABLE_VARIABLE(OnClick) = &TYPE_MEMBER(INTERFACE_TYPE(OnClick), INTERFACE_VTABLE_VARIABLE(OnClick));
* * 
* *     // method body
* *     // ...
* * }
* *
* button.h
* * #pragma once
* * #include "on_click_interface.h"
* * struct Button {
* *     DEFINE_INTERFACE_ADAPTER(OnClick);
* * };
* * 
* * struct Button* TYPE_METHOD(Button, construct_at)(struct Button* const this);
* * struct INTERFACE_TYPE(OnClick)* INTERFACE_GETTER(Button, OnClick)(struct Button* const this);
* * void* TYPE_METHOD(Button, destroy_at)(struct Button* const this);
* * inline static void* TYPE_DYNAMIC_METHOD(Button, destroy_at)(struct Button* const this) {
* *     // any interface with destroy_at is appropriate
* *     return TYPE_DYNAMIC_METHOD(INTERFACE_TYPE(OnClick), destroy_at)(INTERFACE_GETTER(Button, OnClick)(this));
* * }
* *
* button.c
* * #include "button.h"
* * #include <stddef.h>
* * #include <stdlib.h>
* * #include <stdio.h>
* * 
* * void* TYPE_METHOD(Button, destroy_at)(struct Button* const this) {
* *     printf("Button class destructor called\n");
* * 
* *     TYPE_METHOD(INTERFACE_TYPE(OnClick), destroy_at)(&this->INTERFACE_VARIABLE(OnClick));
* *     return this;
* * }
* * 
* * // OnClick overloading
* * // fully boilerplated destroy_at
* * static void* TYPE_METHOD(Button, TYPE_METHOD(INTERFACE_TYPE(OnClick), destroy_at))(struct INTERFACE_TYPE(OnClick)* const interface) {
* *     struct Button* const this = (struct Button* const)((void*)interface - offsetof(struct Button, INTERFACE_VARIABLE(OnClick)));
* *     TYPE_METHOD(Button, destroy_at)(this);
* *     return this;
* * }
* * 
* * void TYPE_METHOD(Button, TYPE_METHOD(INTERFACE_TYPE(OnClick), click))(struct INTERFACE_TYPE(OnClick)* const interface) {
* *     // boilerplate
* *     struct Button* const this = (struct Button* const)((void*)interface - offsetof(struct Button, INTERFACE_VARIABLE(OnClick)));
* *     // method body
* *     printf("Button clicked\n");
* * }
* * 
* * static struct INTERFACE_VTABLE_TYPE(OnClick) CONCAT3(Button, _, INTERFACE_VTABLE_VARIABLE(OnClick)) = {
* *     .click = &TYPE_METHOD(Button, TYPE_METHOD(INTERFACE_TYPE(OnClick), click)),
* *     .destroy_at = &TYPE_METHOD(Button, TYPE_METHOD(INTERFACE_TYPE(OnClick), destroy_at))
* * };
* * 
* * struct INTERFACE_TYPE(OnClick)* INTERFACE_GETTER(Button, OnClick)(struct Button* const this) {
* *     return &this->INTERFACE_VARIABLE(OnClick);
* * }
* * 
* * // Button class non-virtual methods
* * struct Button* TYPE_METHOD(Button, construct_at)(struct Button* const this) {
* *     // boilerplate
* *     TYPE_METHOD(INTERFACE_TYPE(OnClick), construct_at)(&this->INTERFACE_VARIABLE(OnClick));
* *     // methods overloading via vtable change
* *     INTERFACE_GETTER(Button, OnClick)(this)->INTERFACE_VTABLE_VARIABLE(OnClick) = &CONCAT3(Button, _, INTERFACE_VTABLE_VARIABLE(OnClick));
* *     // method body
* *     printf("Button class constructor called\n");
* * 
* *     return this;
* * }
* * 
* main.c
* * #include "button.h"
* * 
* * int main() {
* *     struct Button button;
* *     TYPE_METHOD(Button, construct_at)(&button);
* * 
* *     // call derived object's click method override via OnClick interface method click calling
* *     {
* *         struct INTERFACE_TYPE(OnClick)* const interface = INTERFACE_GETTER(Button, OnClick)(&button);
* *         TYPE_DYNAMIC_METHOD(INTERFACE_TYPE(OnClick), click)(interface);
* *     }
* * 
* *     // destroy derived object via OnClick interface destructor calling
* *     {
* *         struct INTERFACE_TYPE(OnClick)* const interface = INTERFACE_GETTER(Button, OnClick)(&button);
* *         TYPE_DYNAMIC_METHOD(INTERFACE_TYPE(OnClick), destroy_at)(interface);
* *     }
* * 
* *     return 0;
* * }
* * 
*/

#ifdef DEBUG
	#include <assert.h>

	#define ASSERT(EXPR) assert(EXPR)
#else
	#define ASSERT(EXPR)
#endif
