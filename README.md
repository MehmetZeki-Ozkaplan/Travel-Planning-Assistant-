# Travel-Planning-Assistant-
Travel Planning Assistant is a C++ application designed to help users plan their travel routes at major tourist attractions in Sanliurfa.

## 🎯 Project Goals  
- Provide users with a convenient travel plan.  
- Demonstrate real-world applications of data structures and algorithms.  
- Implement file handling, user interaction, and graph-based solutions.

---

## 📋 Features  
- **Route Planning with User Selection**  
  Dynamically plan routes using location IDs.  
- **Graph-Based Shortest Path Calculation**  
  Calculate the shortest route using **Dijkstra's Algorithm**.  
- **File Data Reading**  
  Read location and distance data from `locations.txt` and `distances.txt`.  
- **Sorting Capability**  
  Sort locations by entry fees.  
- **Calculations**  
  Includes total travel time and cost estimations.

---

## 📂 Project File Structure  

```plaintext
📦 sanliurfa-travel-assistant
 ┣ 📜 main.cpp          # Main code file
 ┣ 📜 graph.cpp         # Graph data structure and algorithms
 ┣ 📜 location.cpp      # Location class
 ┣ 📜 locations.txt     # Location information
 ┣ 📜 distances.txt     # Distance information
 ┣ 📜 README.md         # Documentation file


🔧 Setup and Run

   1 - Clone the project folder:

git clone https://github.com/username/sanliurfa-travel-assistant.git
cd sanliurfa-travel-assistant

    2 - Compile and run:

g++ main.cpp graph.cpp location.cpp -o travel_assistant
./travel_assistant

    3 - User Interaction:
When the program runs, users will see a menu. Make your selections to create your travel plan.

📊 Example Outputs
1. Main Menu
📍 Şanlıurfa Gezi Planlama Asistanı 📍
1. Tüm mekanları listele
2. Giriş ücretine göre sıralama
3. Rota planla
4. Çıkış
Seçiminizi giriniz: 


2. List All Locations

ID | Mekan Adı         | Giriş Ücreti (₺) | Ortalama Ziyaret Süresi (dk)
---------------------------------------------------------------
1  | Balıklıgöl        | 10              | 60
2  | Göbeklitepe       | 50              | 120
3  | Harran Evleri     | 20              | 90
4  | Urfa Kalesi       | 15              | 45


3. Route Planning (Based on User Input)

Gezmek istediğiniz mekanların ID'lerini virgülle ayırarak giriniz (örn: 1,3,4): 
1,3,4
En kısa rota hesaplanıyor...
Rota: Balıklıgöl -> Harran Evleri -> Urfa Kalesi
Toplam Mesafe: 25 km
Tahmini Gezi Süresi: 3 saat
Toplam Maliyet: 45₺


4. Sort Locations by Entry Fee

Locations sorted by entry fee:
ID | Location Name      | Entry Fee (₺) | Average Visit Duration (min)
---------------------------------------------------------------
1  | Balıklıgöl         | 10            | 60
4  | Urfa Castle        | 15            | 45
3  | Harran Houses      | 20            | 90
2  | Göbeklitepe        | 50            | 120


📖 Algorithms and Methods

    Graph Structure
    Locations are connected using an adjacency matrix.

    Dijkstra's Algorithm
    Used for shortest distance calculations.

    File Handling
    Data is read from locations.txt and distances.txt.
