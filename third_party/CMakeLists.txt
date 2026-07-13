# GLAD
add_library(glad STATIC src/glad/glad.c)
target_include_directories(glad SYSTEM PUBLIC include/glad)