# Sonicrypt

## Description

Sonicrypt is a compact and intuitive tool designed to enhance the user experience for both buyers and sellers engaging in crypto transactions. Its primary function is to provide immediate auditory and visual confirmation of successful payments, thereby instilling confidence and trust in digital transactions.

## No subscription fees, no hidden costs, completely open-source

Sonicrypt is a completely open-source project, and I am committed to keeping it that way. The device doesn't connect to any of my server or any third-party server. It is a standalone device that you can use without any subscription fees or hidden costs. It only connects to the blockchain network to verify the payment. Both software & hardware are open-source, so you can modify it as you like. Buy your own component, build your own device, and use it as you like.

## Devices

- [x] Sonicrypt
- [ ] Sonicrypt plus (in development)
- [ ] Sonicrypt pro (in development)

### Sonicrypt (standard)

Components:

1. ESP32
2. LED
3. Buzzer

## Features

- [x] Auditory confirmation of successful payments
- [x] Visual confirmation of successful payments
- [ ] Voice confirmation of successful payments (Sonicrypt plus & Sonicrypt pro)
- [ ] Multi-wallet support (Sonicrypt plus & Sonicrypt pro)
- [ ] Multi-chain support (Sonicrypt pro)
- [ ] On the fly QR code generation (Sonicrypt pro)
- [ ] Offchain transactions (Sonicrypt pro)

## User workflow

1. The seller generates a QR code using the Sonicrypt app.
2. The buyer scans the QR code using their wallet app.
3. The buyer sends the payment to the seller.
4. The Sonicrypt device will play a sound and light up when the payment is confirmed & finalized.
5. The seller can then give the product to the buyer.
6. The transaction is complete.

## How it works

1. The Sonicrypt device connects to the blockchain network (solana) websocket to listen to account change
2. The Sonicrypt device listens to the account change of the seller's wallet address
3. When the Sonicrypt device detects a change in the seller's wallet address, it will get the last transaction signature
4. Then it will fetch transaction details using the transaction signature
5. If the transaction is successful, the Sonicrypt device will play a sound and light up
