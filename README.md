## Análisis de componentes principales y procesamiento de lenguage
### TP Integrador 2do cuatrimestre 

### Integrante:
- Ranieri, Martina 1118/22 martubranieri@gmail.com

#### Descripción:
El objetivo de este trabajo es poder clasificar textos que describen películas para identificar el género de la película. Para poder procesar los textos, el dataset que se utiliza en el trabajo, ya está procesado y tenemos únicamente 4 géneros. Los textos son procesados para generar un vector $x_i$ el cual indica la cantidad de veces que aparece un token para la película $i$. En total tenemos 9581 tokens, entonces podemos pensarlo como una matriz de  $\mathcal{R}^{Nx9581}$ siendo N la cantidad de películas. Como las dimensiones de la matriz son muy grandes y tardaríamos mucho en procesarlo, nos vamos a quedar con las 5000/1000/500 tokens más frecuentes.

#### Instalar dependencias
`pip install -r requirements.txt`

#### Contenidos carpetas
* `datos`: Contiene el dataset para el trabajo.
* `graficos`: Contiene imágenes utilizadas en el informe.
* `potencia-deflacion`: Contiene implementación del algoritmo método de la potencia y pruebas utilizadas para el informe sección 3.1.
* `knn`: Contiene implementación del algoritmo KNN y pruebas utilizadas para el informe sección 3.2.
* `pca`: Contiene implementación del algoritmo PCA y pruebas utilizadas para el informe sección 3.3.
* `val-cruzada`: Contiene implementación del validación cruzada y su variante. También de algoritmo TF-IDF y resultados de los experimentos para la sección 3.4 y 4 del informe.