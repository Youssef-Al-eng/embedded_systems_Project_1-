# LED & Pushbutton Embedded Test System

### 📘 Overview
This project demonstrates a modular **Embedded System** developed on **Arduino UNO** using a **layered architecture**.  
The system allows LED control via both **Push Button** and **Serial Communication**, displaying system states on an **LCD**.

---

### 🧩 Project Structure

| Folder | Description |
|:--------|:-------------|
| [📁 **BOM**](./BOM/) | Contains the **Bill of Materials** and **Optimized BOM** tables with component details, prices, and datasheets. |
| [💻 **Code**](./Code/) | Includes all source files — modular drivers for **UART**, **LCD**, **LED**, and **Push Button**. |
| [🧪 **Test**](./Test/) | Contains **test cases**, **validation reports**, and **Arduino Robot Framework scripts**. |
| [📐 **Design**](./Design/) | Holds the **System Architecture**, **UML diagrams**, and **Detailed Design Document** (`design.md`). |
| [🎥 **Video**](./Video/) | Demonstration video showing the system functionality and test results. |

---

### ⚙️ Features
- Modular driver-based architecture (AUTOSAR-like layering)
- UART command interface (`on` / `off`)
- LCD updates with system status
- Button interrupt detection
- LED state synchronization between serial and hardware input
- Unit tests using Robot Framework

---

---

### 🧰 Requirements
- Arduino IDE 2.x  
- AVR-GCC / PlatformIO  
- PlantUML for design visualization  
- Python + Robot Framework (for testing)

---

### 🧑‍💻 Author
**Youssef Alaa**  
The Knowledge Hub Universities – Embedded Systems Project  
📅 *October 2025*  
🏷️ Version: 1.0

---

### 🧱 System Architecture
> You can visualize this diagram using **PlantUML** (copy the code below into [PlantText](https://www.planttext.com) or your IDE plugin):

```plantuml
@startuml
main() --> System_Init()
System_Init() --> LED_Init()
System_Init() --> Button_Init()
System_Init() --> LCD_Init()
System_Init() --> UART_Init()

main() --> Loop()
Loop() --> Button_Read()
Loop() --> LED_Update()
Loop() --> LCD_Display()
Loop() --> UART_Process()
@enduml

