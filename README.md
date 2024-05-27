# ie0217-proyecto
Repositorio para el proyecto Final del curso Estructuras abstractas y algoritmos para ingeniería. 

Grupo de proyecto: 04

**Integrantes del protecto:**

|          **Integrantes**     |**Carné**|
|:----------------------------:|:------:|
| Jason Antonio Luna Vega      | C14345 |
| María José Guevara Matarrita | C13476 |
| Óscar Francisco Rojas Rojas  | C36953 |
  

<br>
<br>  

### ***Introducción:***
En este proyecto se busca optimizar y modernizar la forma en que los agentes bancarios interactúan con los clientes, proporcionando una variedad de operaciones bancarias, desde la atención al cliente hasta la gestión de préstamos y cuentas.

El sistema de gestión bancaria debe cumplir con varios requisitos esenciales para garantizar su funcionalidad y usabilidad. Debe operar en dos modalidades: atención a clientes y consulta de información sobre préstamos, esto permitirá tener opciones predefinidas para distintos tipos de préstamos y generar tablas de pagos personalizadas. Además, gestionará hasta dos cuentas bancarias por cliente (en colones y dólares) y facilitará operaciones como depósitos, retiros, transferencias y abonos a préstamos.

El sistema también debe registrar todas las transacciones, identificando a cada cliente con un número único y gestionando préstamos con características específicas. Se generarán reportes detallados de los préstamos, desglosando cuotas pagadas e intereses.

El proyecto se desarrollará en varias fases: investigación, diseño e implementación. La investigación inicial será documentada y servirá como base para las siguientes fases. En la fase de diseño, se describirá detalladamente el sistema, incluyendo diagramas y explicaciones de su arquitectura y funcionamiento. La implementación combinará la investigación y el diseño, respaldada por pruebas para asegurar la robustez del sistema.

Para gestionar el proyecto, se utilizará un repositorio central en GitHub donde se documentarán todas las fases. Las presentaciones del proyecto se realizarán en tres entregas: Propuesta Proyecto Final, Avance Proyecto Final y Presentación Proyecto Final.

### ***Objetivo General:***  
Diseñar e implementar un sistema de gestión bancaria que cumpla con los requisitos y necesidades de una entidad bancaria, facilitando la gestión de cuentas, prestamos y transacciones.

### ***Objetivos Específicos:***  
1. Proveer un módulo de operación para proporcionar información general sobre diferentes tipos de préstamos.

2. Permitir la realización de depósitos, retiros, transferencias, y abonos a préstamos, además de gestionar múltiples cuentas y certificados de depósito a plazo (CDP).

3. Proporcionar un registro preciso sobre las transacciones realizadas por el cliente.

# Desarrollo:

## Prestamos: 
Un prestatario recibe dinero de un prestamista y mediante un contrato se compromete, a devolverlo según unas cuotas, intereses y plazos acordados por ambas partes. Esta operación, se ha democratizado gracias a los bancos y se ha ido sistematizando y sofisticando con el paso del tiempo. 

## Tipos de préstamos:

•	Préstamo personal: Es un préstamo que no requiere garantía específica, como un vehículo o una propiedad, y generalmente se basa en la solvencia crediticia del solicitante. Las tasas de interés para préstamos personales suelen ser más altas que para préstamos prendarios o hipotecarios, ya que el prestamista asume un mayor riesgo al no tener una garantía tangible. Las tasas de interés pueden ser fijas o variables, y suelen variar según el historial crediticio del solicitante y la política del prestamista.

•	Préstamo prendario: Es un préstamo que está respaldado por una garantía tangible, como un vehículo o una joya. En caso de incumplimiento en el pago del préstamo, el prestamista tiene derecho a tomar posesión de la garantía para recuperar el monto prestado. Las tasas de interés para préstamos prendarios suelen ser más bajas que para préstamos personales, ya que la garantía reduce el riesgo para el prestamista.

•	Préstamo hipotecario: Es un préstamo que está respaldado por una garantía hipotecaria, es decir, una propiedad inmobiliaria. Al igual que en el caso de los préstamos prendarios, si el prestatario no cumple con los pagos del préstamo, el prestamista tiene derecho a tomar posesión de la propiedad. Las tasas de interés para préstamos hipotecarios suelen ser más bajas que para préstamos personales, ya que la propiedad ofrece una garantía más sólida para el prestamista.

•	Certificados de depósito a corto plazo: Los Certificados de Depósito a corto plazo (CDP) son instrumentos financieros de renta fija emitidos por bancos u otras instituciones financieras. Un inversionista deposita dinero a cambio de un certificado que garantiza el pago de capital e intereses al vencimiento. Tienen vencimientos de menos de un año y ofrecen tasas de interés más altas que las cuentas de ahorro estándar. Pueden implicar penalizaciones por retiro anticipado. Son considerados seguros debido a que están respaldados por la solidez financiera de la institución emisora

•	Préstamos asociados: Los préstamos asociados son créditos que se relacionan con la compra de un bien o servicio específico ofrecido por el prestamista. Se emplean comúnmente para financiar la adquisición de cosas como vehículos, viviendas o dispositivos tecnológicos.

Estos préstamos requieren que el dinero prestado sea usado exclusivamente para la compra del bien o servicio asociado. Por lo general, presentan condiciones especiales, como tasas de interés y plazos de amortización, que pueden ser más favorables que las de un préstamo estándar debido a la garantía que representa el bien adquirido.

En caso de no cumplir con los pagos del préstamo, el prestamista puede tomar acciones para recuperar el bien o servicio financiado, ya que suelen estar respaldados por un contrato de garantía específico.

## Tasas de interés: 
La tasa de interés es un monto de dinero que normalmente corresponde a un porcentaje de la operación de dinero que se esté realizando.

•	Depósitos: La tasa de interés expresa el pago que recibe la persona o empresa que deposita el dinero por poner esa cantidad a disposición de otro.

•	Créditos: La tasa de interés es el monto que el deudor deberá pagar a quien le presta, por el uso de ese dinero.

## Capital:
Es uno de los cuatro factores de producción y se refiere a bienes durables y recursos financieros usados para producir otros bienes y servicios. Es esencial para generar riqueza y mejorar los procesos productivos, facilitando el crecimiento económico.

Se clasifica en:

•	Según el propietario: capital público y privado.

•	Según la constitución: capital físico e intangible.

•	Según el plazo: capital a corto y largo plazo.

•	Según su uso: capital social, de riesgo y flotante.

## Interés: 
Es la cantidad extra que se añade al devolver el capital solicitado o al recuperar una inversión. Es fundamental para mantener una buena salud financiera y entender la rentabilidad de las inversiones y el costo de los préstamos.

Tipos de Interés:

Según su naturaleza:
•	Interés simple: Se genera sobre el capital inicial.

•	Interés compuesto: Se suma al capital general y genera nuevos intereses.

Según el préstamo o crédito:
•	Tipo de interés fijo: Permanece igual durante todo el plazo del préstamo.

•	Tipo de interés variable: Puede cambiar durante la operación financiera, basado en índices como la inflación o el Euribor.

En los préstamos:
•	TIN (Tipo de Interés Nominal): Porcentaje fijo pactado por el dinero prestado.
•	TAE (Tasa Anual Equivalente): Indica el coste efectivo de los préstamos, incluyendo comisiones y gastos.

En las hipotecas:
•	Interés fijo: No cambia durante el plazo.
•	Interés variable: Varía con el tiempo.
•	Interés mixto: Combinación de fijo y variable.

En las tarjetas de crédito:
•	Interés de saldos excedidos: Se aplica al superar el límite de crédito.
•	Interés de demora: Se aplica cuando no se paga a tiempo.

## Explicación del tipo de cambio 
El tipo de cambio es la tasa a la que se puede cambiar una moneda por otra. Este tipo varía continuamente en los mercados mundiales de divisas.

Precio de Compra y Venta

•	Precio de compra: Es la tasa a la que se puede vender una moneda para obtener otra.

•	Precio de venta: Es la tasa a la que se puede comprar una moneda utilizando otra.

 Funcionamiento del Tipo de Cambio

•	Mercados de Divisas: Los tipos de cambio fluctúan en los mercados de divisas donde se negocian las monedas.

•	Tipos de referencia: Se publica diariamente los tipos de cambio de referencia en la media de los precios de compra y venta.

•	Tipo de Cambio Efectivo Nominal: Indica el costo promedio de cambiar monedas extranjeras basado en las medias ponderadas.

Influencia en la Economía

•	Exportaciones: Un tipo de cambio favorable, donde la moneda local se deprecia, hace que los productos locales sean más baratos en el extranjero, lo que impulsa las exportaciones al aumentar su competitividad.

•	Importaciones: Un tipo de cambio desfavorable, donde la moneda local se aprecia, hace que los productos extranjeros sean más baratos para los consumidores locales, lo que puede aumentar las importaciones.

•	Política Monetaria: El tipo de cambio, es un factor que afecta la estabilidad de precios y el comercio internacional, influyendo indirectamente en la política monetaria.

## Referencias
1.	Communications. (2023, 18 enero). Qué es un préstamo financiero: tipos y diferencias con un crédito. BBVA NOTICIAS. https://www.bbva.com/es/salud-financiera/que-es-un-prestamo-financiero-tipos-y-diferencias-con-un-credito/
2.	iProfesional. (2024). Qué tipo de préstamos existen y cómo saber cuál me conviene. Recuperado de [enlace](URL)

3.	Banco de Crédito del Perú (BCP). (2023). ¿Cómo sacar el interés de un préstamo personal y cómo funcionan? Recuperado de [enlace](URL)

4.	Aprende Economía. (2024). Cómo la tasa de interés afecta tus decisiones financieras. Recuperado de [enlace](URL)

5.	Perspectivas de PNC. (2024). Explicación de las tasas de interés hipotecario: ¿Qué es una tasa de interés hipotecario? Recuperado de [enlace](URL)
6.	Coll Morales, F. (2021, 11 de febrero). Préstamo bancario - Qué es, definición y concepto. Economipedia. Recuperado de [https://economipedia.com/definiciones/prestamo-bancario.html](https://economipedia.com/definiciones/prestamo-bancario.html)
7.	Westreicher, G. (2019, 6 de octubre). Tipos de créditos - Definición, qué es y concepto. Economipedia. Recuperado de [https://economipedia.com/definiciones/tipos-de-creditos.html](https://economipedia.com/definiciones/tipos-de-creditos.html)
8.	Gutiérrez, M. E. (2020). Préstamo. Enciclopedia Iberoamericana. Recuperado de [https://enciclopediaiberoamericana.com/definiciones/prestamo.html](https://enciclopediaiberoamericana.com/definiciones/prestamo.html)
9.	CMF Educa  ¿Qué es la Tasa de Interés? (s. f.). CMF Educa  Comisión Para el Mercado Financiero. https://www.cmfchile.cl/educa/621/w3article27164.html
10.	Santander, B. (s. f.). ¿Qué es el capital en economía? Banco Santander. https://www.bancosantander.es/glosario/capital
11.	Coca, M. (2023b, agosto 17). ¿Qué es el interés y qué tipos de interés existen? BBVA NOTICIAS. https://www.bbva.com/es/saludfinanciera/queeselinteresyquetiposdeinteresexisten/
12.	European Central Bank. (2021, 18 noviembre). ¿Cuál es la función de los tipos de cambio? https://www.ecb.europa.eu/ecbandyou/explainers/tellmemore/html/role_of_exchange_rates.es.html


|<span style="color: Blue;">**_Fase_** </span>|<span style="color: Brown;">**_Actividad_** </span>|<span style="color: Orange;">**_Duración_** </span>|<span style="color: Purple;">**_Responsables_** </span>|<span style="color: Green;">**_Inicio_** </span>|<span style="color: Red;">**_Fin_** </span>|
|-----------------------------|-----------------------------------------|-----------|---------------------------|------------|------------|
| Investigación               | Recopilación de información             | 3 Días    | Todos                     | 15/05/2024 | 17/05/2024 |
|                             | Elaboración del archivo Markdown        | 3 Días    | Todos                     | 18/05/2024 | 21/05/2024 |
| Diseño                      | Diseño del esquema de la base de datos  | 2 Días    | Jason                     | 20/05/2024 | 21/05/2024 |
|                             | Diseño de diagramas de flujo            | 1 Día     | Jason                     | 23/05/2024 | 24/05/2024 |
|                             | Planificación y cronograma              | 1 Día     | Óscar                     | 24/05/2024 | 25/05/2024 |
|**Propuesta proyecto final** | Presentar la primera fase del proyecto  | 1 dia     | Todos                     | 27/05/2024 | 27/05/2024 |
|Implementación               | Implementar clases                      | 1 semana  | Persona**                 | 30/05/2024 | 06/06/2024 |
|                             | Integrar clases                         | 1 semana  | Persona**                 | 06/06/2024 | 13/06/2024 |
| Pruebas                     | Pruebas unitarias                       | 1 Dia     | Óscar                     | 13/06/2024 | 14/06/2024 |
|                             | Pruebas de integración                  | 2 Dias    | María José                 | 13/06/2024 | 15/06/2024 |
|                             | Pruebas de aceptación                   | 1 Dia     | Óscar                     | 14/06/2024 | 15/06/2024 |
|**Preparación de exposición**| Preparar exposición del avance          | 2 Dias    | Todos                     | 15/06/2024 | 17/06/2024 |
|**Avance Proyecto Final**    | Presentar el avance de proyecto         | 1 Día     | Todos                     | 17/06/2024 | 17/06/2024 |
|**Presentación Proyecto Final**| Revisión general del proyecto         | 1 Día     | Todos                     | 14/07/2024 | 15/07/2024 |
|                             | Presentar el proyecto                   | 1 Día     | Persona**                 | 16/07/2024 | 16/07/2024 |