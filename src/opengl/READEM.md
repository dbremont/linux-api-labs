# Rednering Raster Graphics

1. **Abstraction over OpenGL**
   SFML provides an abstraction layer over raw OpenGL calls. When you draw something like an `sf::Sprite` or an `sf::Texture`, SFML internally translates those calls into appropriate OpenGL commands.

2. **Textures as OpenGL Textures**
   SFML loads images (e.g., PNG, JPG) into memory and creates OpenGL texture objects (`GLuint` texture IDs). These textures live on the GPU and are used during rendering.

3. **Vertex Arrays and Buffers**
   SFML represents drawable objects (sprites, shapes) as sets of vertices with attributes like position, texture coordinates, and color. These vertices are stored in client memory or in GPU buffers (like Vertex Buffer Objects, VBOs).

4. **Shaders and the Graphics Pipeline**
   SFML uses OpenGL shaders (usually vertex and fragment shaders) to transform vertices and apply textures during rendering. SFML has default shaders internally, but it also allows users to provide custom shaders.

5. **Rendering Process**
   When you call `window.draw(sprite)` in SFML:

   * SFML binds the associated OpenGL texture.
   * It sets up vertex data for the sprite's quad (two triangles).
   * It applies the current transform matrix (position, rotation, scale).
   * It executes OpenGL draw calls (`glDrawArrays` or `glDrawElements`) to rasterize the textured quad on screen.

6. **Context Management**
   SFML creates and manages the OpenGL context for the window behind the scenes, ensuring all OpenGL commands are valid and synchronized.
