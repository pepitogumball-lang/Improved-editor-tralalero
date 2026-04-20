# Improved Editor Tralalero

Un mod avanzado para Geode que revoluciona el editor de Geometry Dash reorganizando los bloques en hubs categorizados inteligentes.

## Características Principales 🔥

- **Hubs Categorizados**: Al seleccionar una categoría, se abre un popup con subcategorías organizadas.
- **Búsqueda en Tiempo Real 🔍**: Campo de búsqueda para filtrar bloques por ID o nombre.
- **Sistema de Favoritos ⭐**: Agrega bloques a favoritos con un clic, y accede rápidamente a ellos.
- **Scroll Infinito**: Grid con scroll para manejar cientos de bloques sin problemas.
- **Múltiples Categorías**: Soporte completo para bloques, triggers, decoraciones y más.
- **Interfaz Moderna**: Diseño limpio con botones intuitivos y animaciones suaves.

## Categorías Disponibles

### 🧱 Bloques (ID 1)
- Bloques Básicos: Normales, especiales
- Slopes: Todas las pendientes
- Spikes: Pinchos de todos tipos
- Orbes: Portales amarillos, azules, etc.
- Portales: Speed, gravity, etc.
- Pads: Jump pads, dash pads
- Rings: Coin rings, etc.
- Hazards: Saw blades, etc.

### ⚙️ Triggers (ID 2)
- Move: Mover objetos
- Rotate: Rotar
- Scale: Escalar
- Alpha: Transparencia
- Toggle: On/Off
- Spawn: Spawnear
- Animate: Animaciones
- Follow: Seguir player

### 🎨 Decoraciones (ID 3)
- Fondo: Elementos de fondo
- Ground: Decoraciones terrestres
- Animado: Decoraciones con animación
- Efectos: Partículas y efectos

## Instalación Automática 🚀

Gracias a GitHub Actions, el mod se compila automáticamente para Android64 y Android32.

1. Descarga el `.geode` desde [Releases](https://github.com/pepitogumball-lang/Improved-editor-tralalero/releases)
2. Instala con Geode Loader
3. ¡Disfruta!

## Compilación Manual (Desarrolladores)

```bash
git clone https://github.com/pepitogumball-lang/Improved-editor-tralalero
cd Improved-editor-tralalero
mkdir build && cd build
cmake .. -DGEODE_TARGET_PLATFORM=Android64
make
```

Asegúrate de tener Geode SDK configurado.

## Uso en el Editor

1. Abre el editor de niveles en GD
2. Selecciona una categoría (bloques, triggers, etc.)
3. Se abre el BlockHub con subcategorías
4. Usa búsqueda o favoritos para encontrar bloques rápido
5. Click en un bloque para seleccionarlo
6. Click ⭐ para agregarlo a favoritos

## Contribuciones

¡Bienvenido! Abre issues para bugs o sugerencias, o PRs para mejoras.

## Licencia

MIT License - Úsalo libremente, pero atribuye.

## Créditos

- Desarrollado con ❤️ usando Geode SDK
- Inspirado en la comunidad de modding de GD

Para más información sobre Geode SDK, visita [Geode Docs](https://docs.geode-sdk.org/).