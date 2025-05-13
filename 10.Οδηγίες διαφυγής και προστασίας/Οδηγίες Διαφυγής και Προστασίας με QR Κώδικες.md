**Περιπτώσεις πυρκαγιάς ή σεισμού**

Κώδικας QR με ένα ανοιχτό λογισμικό QR code generator που όταν σκαναριστεί, παρέχει λεπτομέρειες για τις διαδρομές διαφυγής και τις οδηγίες έκτακτης ανάγκης.

Κόστος: 0,1 ευρώ (Η τιμή του αυτοκόλλητου Α4.Θα το φτιάξουμε εμείς).

![QR Code Example](https://github.com/2o-gym-chrys/UNBEATABLES/blob/main/10.%CE%9F%CE%B4%CE%B7%CE%B3%CE%AF%CE%B5%CF%82%20%CE%B4%CE%B9%CE%B1%CF%86%CF%85%CE%B3%CE%AE%CF%82%20%CE%BA%CE%B1%CE%B9%20%CF%80%CF%81%CE%BF%CF%83%CF%84%CE%B1%CF%83%CE%AF%CE%B1%CF%82/QR%20CODE%20%CE%9F%CE%94%CE%97%CE%93%CE%99%CE%95%CE%A3%20%CE%94%CE%99%CE%91%CE%A6%CE%A5%CE%93%CE%97%CE%A3%20%CE%9A%CE%91%CE%99%20%CE%A0%CE%A1%CE%9F%CE%A3%CE%A4%CE%91%CE%A3%CE%99%CE%91%CE%A3.png?raw=true)



Ο QR Κώδικας δημιουργήθηκε με:

**QR Code Generator**

Αυτό το project δημιουργεί QR Codes από URLs με χρήση της βιβλιοθήκης `QRCode.js`.

Τι περιέχει αυτός ο απλός κώδικας:

Ένα HTML αρχείο 

Μια JavaScript βιβλιοθήκη για QR codes:

qrcode.min.js από https://github.com/soldair/node-qrcode

Διατίθεται με MIT License, που είναι ανοιχτή άδεια χρήσης


**ΟΔΗΓΙΕΣ ΓΙΑ ΝΑ ΔΗΜΙΟΥΡΓΗΣΕΤΕ ΚΩΔΙΚΑ**

1.Άνοιξε το Σημειωματάριο (Notepad) ή έναν επεξεργαστή κειμένου

2.Κάνε αντιγραφή τον παρακάτω κώδικα
3.  Αποθήκευσέ το ως:qr.html   (Πρόσεξε: άλλαξε την κατάληξη από .txt σε .html)

Π.χ. στο Σημειωματάριο:

"Αρχείο" > "Αποθήκευση ως..."

Όνομα αρχείου: qr.html

Αποθήκευση ως τύπος: "Όλα τα αρχεία"

Κωδικοποίηση: UTF-8

4. Άνοιξέ το με διπλό κλικ
Θα ανοίξει στον browser σου (Chrome, Edge, Firefox) και θα δεις μια φόρμα:

Πληκτρολογείς ένα URL

Πατάς "Φτιάξε QR"

Εμφανίζεται το QR code εκείνη τη στιγμή


[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)


**Χρησιμοποιούμενος Κώδικας**.**Ακολουθεί ο κώδικας HTML και JavaScript για τη δημιουργία του QR code:**


```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>QR Generator</title>
    <script src="https://cdn.jsdelivr.net/npm/qrcode@1.5.0/build/qrcode.min.js"></script>
  </head>
  <body style="font-family: Arial, sans-serif; text-align: center; padding: 40px;">

    <h2>Δημιουργία QR Code</h2>
    <p>Γράψε μία διεύθυνση (URL) για να δημιουργήσεις έναν QR κωδικό</p>

    <input id="text" type="text" placeholder="https://example.com" style="width: 300px; padding: 10px;">
    <br><br>
    <button onclick="generateQRCode()" style="padding: 10px 20px; font-size: 16px;">Φτιάξε QR</button>

    <div id="qrcode" style="margin-top: 30px;"></div>

    <p style="font-size: 14px; color: gray; margin-top: 40px;">
      Κατασκευάστηκε με χρήση ανοιχτού κώδικα (MIT License) – Βιβλιοθήκη: 
      <a href="https://github.com/soldair/node-qrcode" target="_blank">QRCode.js</a>
    </p>

    <script>
      function generateQRCode() {
        const text = document.getElementById("text").value;
        document.getElementById("qrcode").innerHTML = "";

        if (text.trim() === "") {
          alert("Παρακαλώ γράψε ένα URL!");
          return;
        }

        QRCode.toCanvas(document.createElement('canvas'), text, function (error, canvas) {
          if (error) {
            console.error(error);
            alert("Κάτι πήγε στραβά!");
            return;
          }
          document.getElementById("qrcode").appendChild(canvas);
        });
      }
    </script>

  </body>
</html>
