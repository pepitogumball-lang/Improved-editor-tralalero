# Improved Editor Tralalero

Un mod para Geode que mejora el editor de Geometry Dash reorganizando los bloques en hubs categorizados.

## Características

- Al seleccionar una categoría en el editor, se abre un hub con subcategorías.
- Cada subcategoría muestra bloques organizados en un grid con scroll.
- Campo de búsqueda para filtrar bloques por ID.
- Botón de cerrar para salir del hub.
- Soporte para múltiples categorías: bloques, triggers, decoraciones, etc.

## Categorías Implementadas

### Bloques (ID 1)
- Cuadrados
- Slopes
- Glow
- Spikes
- Orbes

### Triggers (ID 2)
- Move
- Rotate
- Scale

## Instalación

1. Asegúrate de tener Geode 5.6.1 o superior instalado.
2. Compila el mod para Android64 o Android32.
3. Instala el .geode en tu dispositivo.

## Compilación

Usa CMake para compilar:

```bash
mkdir build
cd build
cmake ..
make
```

Asegúrate de tener la variable de entorno `GEODE_SDK` apuntando al directorio del SDK de Geode.

## Desarrollo

El código principal está en:
- `src/main.cpp`: Hook principal.
- `src/BlockHubPopup.cpp`: Implementación del popup del hub.

Para más información sobre Geode SDK, visita [Geode Docs](https://docs.geode-sdk.org/).