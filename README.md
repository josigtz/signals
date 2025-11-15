# Procesamiento Digital de Señales (DSP)

Repositorio de implementaciones prácticas en C para el procesamiento de señales de audio en formato WAV. Este proyecto contiene diversas técnicas de procesamiento de señales aplicadas a archivos de audio.

## 📋 Descripción

Este repositorio contiene implementaciones educativas de algoritmos fundamentales de procesamiento digital de señales (DSP) en lenguaje C. Cada módulo trabaja con archivos WAV y demuestra técnicas específicas de manipulación y análisis de señales de audio.

## 🗂️ Estructura del Proyecto

### 01_ReduccionDeVolumen
Implementación de reducción de volumen de archivos de audio.
- **Archivo principal**: `reduccion.c`
- **Funcionalidad**: Reduce el volumen de una señal de audio dividiéndola por 2
- **Uso**:
  ```bash
  ./reduccion entrada.wav salida.wav
  ```

### 02_Convolucion
Implementaciones de filtros FIR (Finite Impulse Response) e IIR (Infinite Impulse Response).
- **Archivos principales**:
  - `convolucion.c` - Implementación básica de convolución
  - `FIR_LP.c` - Filtro pasa-bajos FIR
  - `FIR_LP_int16.c` - Filtro FIR optimizado para enteros de 16 bits
  - `IIR_LP.c` - Filtro pasa-bajos IIR
- **Funcionalidad**: Filtrado de señales mediante convolución con respuesta al impulso
- **Características**:
  - Generación de respuesta al impulso exponencial
  - Frecuencia de corte: 2000 Hz
  - Frecuencia de muestreo: 44100 Hz

### 03_DFT
Transformada Discreta de Fourier (DFT).
- **Archivo principal**: `dft.c`
- **Funcionalidad**: Calcula la DFT de una señal de audio para análisis en el dominio de la frecuencia
- **Archivos adicionales**:
  - `DFT.m` - Implementación en MATLAB
  - `transformada.xlsx` - Resultados de ejemplo

### 04_IDFT
Transformada Discreta Inversa de Fourier (IDFT).
- **Archivo principal**: `idft.c`
- **Funcionalidad**: Reconstruye una señal temporal a partir de su representación en frecuencia
- **Uso**: Complementa la DFT para análisis bidireccional tiempo-frecuencia

### 05_Multiplicación
Multiplicación de señales en el dominio del tiempo.
- **Archivo principal**: `multiplicacion.c`
- **Funcionalidad**: Multiplica dos señales de audio punto por punto
- **Aplicaciones**: Modulación de amplitud, ventaneo, efectos de audio

### DMF (DTMF)
Decodificador de tonos DTMF (Dual-Tone Multi-Frequency).
- **Archivo principal**: `dmf.c`
- **Funcionalidad**: Detecta dígitos telefónicos a partir de tonos DTMF
- **Frecuencias implementadas**:
  - Bajas: 697, 770, 852, 941 Hz
  - Altas: 1209, 1336, 1477, 1633 Hz
- **Dígitos detectables**: 0-9, A-D, *, #
- **Uso**:
  ```bash
  ./dmf entrada.wav
  ```

### z transform
Implementación de transformada Z y análisis de respuesta al impulso.
- **Archivo principal**: `respuestaImpulso.c`
- **Funcionalidad**: Análisis de sistemas en el dominio Z

## 🔧 Requisitos

- Compilador GCC o compatible
- Sistema operativo: Linux/Unix (también compatible con Windows mediante MinGW)
- Archivos de audio en formato WAV (PCM, 16 bits recomendado)

## 📦 Compilación

Para compilar cualquier módulo, utiliza el siguiente comando:

```bash
gcc -o programa archivo.c -lm
```

Ejemplo:
```bash
gcc -o reduccion 01_ReduccionDeVolumen/reduccion.c -lm
gcc -o dmf DMF/dmf.c -lm
gcc -o convolucion 02_Convolucion/convolucion.c -lm
```

La flag `-lm` es necesaria para enlazar la biblioteca matemática.

## 🚀 Uso General

La mayoría de los programas siguen el patrón:

```bash
./programa archivo_entrada.wav archivo_salida.wav
```

Excepto el decodificador DTMF que solo requiere entrada:

```bash
./dmf archivo_tono.wav
```

## 📚 Estructura de Archivos WAV

Todos los programas trabajan con la siguiente estructura de cabecera WAV:

```c
struct HEADER {
    char    id[4];              // "RIFF"
    int32_t totallength;        // Tamaño total
    char    wavefmt[8];         // "WAVEfmt "
    int32_t format;             // 16 para PCM
    int16_t pcm;                // 1 para PCM
    int16_t channels;           // Número de canales
    int32_t frequency;          // Frecuencia de muestreo
    int32_t bytes_per_second;   // Tasa de bytes
    int16_t bytes_by_capture;   // Bytes por captura
    int16_t bits_per_sample;    // Bits por muestra
    char    data[4];            // "data"
    int32_t bytes_in_data;      // Tamaño de datos
};
```

## 📖 Documentación Adicional

Cada directorio contiene reportes en formato DOCX con:
- Fundamentos teóricos
- Desarrollo matemático
- Resultados experimentales
- Análisis de señales

## 🎯 Aplicaciones

Este repositorio es útil para:
- Aprendizaje de procesamiento digital de señales
- Prácticas de laboratorio de DSP
- Implementación de filtros digitales
- Análisis de señales de audio
- Decodificación de tonos telefónicos
- Comprensión de transformadas tiempo-frecuencia

## ⚠️ Notas Importantes

- Los programas asumen archivos WAV en formato PCM con muestras de 16 bits
- Se recomienda trabajar con frecuencias de muestreo estándar (44100 Hz)
- Algunos programas incluyen valores hardcodeados para pruebas específicas
- Los archivos de salida mantienen el mismo formato que los de entrada

## 🔬 Técnicas Implementadas

1. **Procesamiento en el dominio del tiempo**
   - Reducción de volumen
   - Multiplicación de señales

2. **Convolución**
   - Filtros FIR
   - Filtros IIR
   - Respuesta al impulso exponencial

3. **Análisis frecuencial**
   - DFT (Transformada Discreta de Fourier)
   - IDFT (Transformada Inversa)
   - Detección de frecuencias específicas (DTMF)

4. **Análisis en Z**
   - Transformada Z
   - Respuesta al impulso

## 📝 Licencia

Proyecto educativo para el aprendizaje de procesamiento digital de señales.

## 🤝 Contribuciones

Este es un proyecto educativo. Los reportes y archivos de ejemplo están incluidos con fines demostrativos.
