#include <stdio.h>
#include <string>

using namespace std;

typedef void *animal_t;

struct animal_impl;

typedef struct animal_ops {
    void (*speak)(const struct animal_impl *impl);
    void (*free)(struct animal_impl *impl);
} animal_ops_t;

typedef struct animal_impl {
    animal_ops_t ops;
} animal_impl_t;

typedef struct cat_impl {
    animal_impl_t animal_impl;
    char *name;
} cat_impl_t;

typedef struct horse_impl {
    animal_impl_t animal_impl;
} horse_impl_t;

void speak_cat(const animal_impl *impl) {
    printf("meow! my name is %s\n", ((const cat_impl *)impl)->name);
}

void speak_horse(const animal_impl *impl) {
    printf("neigh!\n");
}

void free_cat(animal_impl_t *impl) {
    cat_impl_t *cat_impl = (cat_impl_t *) impl;
    free(cat_impl->name);
    free(cat_impl);
}

void free_horse(animal_impl_t *impl) {
    free(impl);
}

void speak_animal(animal_t animal) {
    animal_impl_t *impl = (animal_impl_t *) animal;
    impl->ops.speak(impl);
}

animal_t make_cat(const char *name) {
    cat_impl_t *impl = (cat_impl_t *) malloc(sizeof(cat_impl_t));
    if (!impl) {
        return NULL;
    }

    impl->animal_impl.ops = {
        &speak_cat,
        &free_cat
    };
    impl->name = _strdup(name);

    return impl;
}

animal_t make_horse() {
    horse_impl_t *impl = (horse_impl_t *) malloc(sizeof(horse_impl_t));
    if (!impl) {
        return NULL;
    }

    impl->animal_impl.ops = {
        &speak_horse,
        &free_horse
    };

    return impl;
}

void free_animal(animal_t animal) {
    animal_impl_t *impl = (animal_impl_t *) animal;
    impl->ops.free(impl);
}
int main()
{
    animal_t cat = make_cat("mittens");
    animal_t horse = make_horse();

    speak_animal(cat);
    speak_animal(horse);

    free_animal(cat);
    free_animal(horse);
}
