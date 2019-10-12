 // shape.c
struct Shape {
   ShapeType* type;
   char buffer_start;
};

struct ShapeType {
   int buffer_size;
   const char* (*name)(Shape*);
   int (*sides)(Shape*);
   void (*destroy)(Shape*);      
};

ShapeType* ShapeType__create(
     int buffer_size,
     const char* (*name)(Shape*),
     int (*sides)(Shape*),
     void (*destroy)(Shape*)) {
   ShapeType* result = (ShapeType*) malloc(sizeof(ShapeType));
   result->buffer_size = buffer_size;
   result->name = name;
   result->sides = sides;
   result->destroy = destroy;
   return result;
}

Shape* Shape__create(ShapeType* type) {
  int size = sizeof(Shape) + type->buffer_size;
  Shape* result = (Shape*) malloc(size);
  result->type = type;
  return result;
}

ShapeType* Shape__type(Shape* self) {
  return self->type;
}

void* Shape__buffer(Shape* self) {
   return (void*) &(self->buffer_start);
}

int Shape__sides(Shape* self) {
  return self->type->sides(self);
}

void Shape__destroy(Shape* shape) {
   if (shape) {
      shape->type->destroy(shape);
   }
}

