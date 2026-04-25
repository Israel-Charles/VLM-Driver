# Putting It All Together

## 1. Mounting the Mounting Deck to the Chassis

1. **Gently place the Upper Level Chassis (Mounting Deck assembly)** onto the standoffs of the Lower Level Chassis.  
   - The **VESC should be toward the rear of the vehicle**.  
   - Route the **PPM cable from the servo motor** on the Lower Level Chassis through one of the **Mounting Deck slots**.

   ![Upper Level Chassis placed on Lower Level Chassis.](img/together_NX_00.JPG)

   > ### ***Note that the Powerboard shown above is outdated. The updated design differs. Below is the current Powerboard layout.***
   >
   > ![Powerboard](img/PowerboardLayout.jpg)

2. **Secure the Mounting Deck** to the standoffs on the Lower Level Chassis:
   - Use **three M3 screws**.
   - Optionally, use a **zip tie** to secure the USB cable from the lidar.

> ### **Warning:**
>
> The **driveshaft** running along the chassis rotates during movement. Ensure all cables and wires are **kept clear of rotating parts**, including the driveshaft, to prevent damage.

---

## 3. Connecting the Brushless Motor to the VESC

1. **Prepare three 4mm to 3.5mm bullet adapters**.

   ![Bullet adapters.](img/together07.png)

2. **Attach the adapters** to the **blue, yellow, and white wires** of the brushless motor.

   ![Brushless Motor wires.](img/together08.JPG)

3. **Connect the VESC to the motor**:
   - The **VESC has three labeled outputs: A, B, and C**.

   ![VESCMKIII.](img/together10.jpg)

   - Wire mapping:
     - **A → WHITE**
     - **B → YELLOW**
     - **C → BLUE**

   ![Brushless Motor connected to VESC.](img/together09.JPG)

> ### **Important:**
>
> If the vehicle moves **backwards after VESC setup**, swap the **WHITE wire to C** and the **BLUE wire to A**.

---

## 4. Connecting the Battery to the VESC

1. **Plug the charge adapter into the battery connector**.

   ![Charge adapter connected to Lipo battery.](img/llchassis15.JPG)

   > ### **Danger: Battery**
   >
   > Ensure **RED (POWER)** and **BLACK (GROUND)** are connected correctly.  
   > Incorrect wiring may result in **fire or damage**.

2. **Connect the charge adapter to the TRX-to-XT90 adapter**.

   ![Connecting TRX to XT90 adapter.](img/llchassis16.JPG)

3. **Final battery connection setup**:

   ![TRX to XT90 adapter installed.](img/llchassis17.JPG)

4. **Final powered system state**:

   ![Battery connected to VESC.](img/BatteryConnected.jpg)

---

## 5. Connecting the NVIDIA Jetson NX to the Powerboard

1. The **Jetson NX** is powered through the **Powerboard**.  
   - Use a **male-to-male barrel jack cable (2.5mm x 5.5mm)** to connect the Jetson to the Powerboard.  
   - **Center pin is POWER**.

   > ### **Warning: Power Wiring**
   >
   > Barrel jack polarity is not standardized.  
   > Do **not** connect a supply where the **center pin is ground**, as this may damage the system.

   ![Jetson NX power supply connected to Powerboard.](img/JetsonConnect.jpg)

   > ### Note:
   > The Powerboard outputs **19V** for the Jetson. If your compute device requires a different voltage, use a **buck converter** to step down the voltage appropriately.

---

## 6. Connecting the Lidar

1. The lidar comes with **two long cables**. Route them carefully through the slots in the **Mounting Deck** to prevent snagging.

2. **Connect the Lidar to the NVIDIA Jetson NX**:
   - **UTM-30LX** → Connect via **USB hub**.
   - **UST-10LX** → Connect via **Ethernet port**.

3. **Connect Lidar power supply**:

> **Danger:**  
> **BROWN = POWER**, **BLUE = GROUND**.  
> Reversing these will permanently damage the lidar. Always verify the wiring label.

   ![Lidar power connected to terminal block.](img/LidarConnect.jpg)

---

## 7. Attaching the PPM Cable

1. **Locate the PPM cable**:
   - One end is **white**, the other is **black**.

   ![PPM cable.](img/llchassis21.JPG)

2. **Take three header pins**.

   ![Header pins.](img/llchassis18.JPG)

3. **Insert header pins into the servo wires**.

   ![Header pin connected to Servo cable.](img/llchassis19.JPG)

4. **Connect the PPM cable to the servo**.

   > **Danger:**
   > **BROWN is GROUND** and must connect to the **BLACK servo wire**.

   ![PPM cable connected to Servo cable.](img/llchassis20.JPG)

5. **Connect the PPM cable to the VESC**.

   ![PPM cable plugged into VESC.](img/together_NX_04.JPG)

---

## 8. Final Touches

1. **Connect the micro USB cable** (white cable) from the **VESC to the USB hub**.

   ![Micro USB connected to VESC.](img/together_NX_08.JPG)

2. **Screw on the antennas** onto the antenna terminals.

---

## 9. Done!

Your completed **Vehicle Assembly** should look like this:

   ![Final assembled vehicle.](img/final.JPG)

---

## *Acknowledgements*

>*This vehicle build is based on and follows a design philosophy similar to the open-source autonomous vehicle platform **RoboRacer (F1TENTH ecosystem)**.*  
