# Part 0: Basic Message Sending

We have given you the code for `server0`, which expects an unencrypted message from the client and returns a response. Implement the corresponding `client0` code so that it prints out the message it receives from the server.

# Part 1: Basic Asymmetric Encryption

Protocol ver.0 is obvious pretty bad. We're sending messages in the clear, and anyone can snoop on the traffic and see our messages. To deal with this, we're going to use a Diffie-Hellman key exchange to derive a shared key without revealing it to a third party.

Implement the party `client1`. The client should initiate a Diffie-Hellman key exchange with the server and print out the decrypted message it receives.

# Part 2: Signature Authentication

Protocol ver.1 is better, but it's still susceptible to man-in-the-middle attacks. In this new version, the server will sign its initial handshake so the client is more certain who it's talking to. 

Implement `client2`. The new client must verify the signature sent by the server and print out either `Handshake authenticated!` or `Failed to authenticate!` depending on the result of the signature verification. As before, the client should also print out the decrypted message it receives. 

# Part 3: Verifying with a CA

Protocol ver.2 is slightly better, but the client still implicitly trusts the server's identity. A man-in-the-middle can still impersonate the server. We are now going to fix that. We have provided a party `ca_auth` that acts as a certificate authority (CA). A server generates a certificate by sending its public key to the CA for the CA to sign.

For this part, you will need to do the following:
 1.  Finish implementing the party `server_setup`. This is the code for requesting a new certificate from a CA. Notice that the `server_setup` party writes its public certificate and corresponding secret key to a file for `server3` to use. 
 2.  Run `./server_setup.sh` to generate a certificate for the server. This helper script simply runs the `ca_auth` and `server_setup` parties.
 3.  Implement the party `client3`. This client should verify that the server's certificate was indeed signed by the CA **before** it verifies the handshake signature. 

This version of the protocol also has both the server and client use an additional _random nonce_ in the handshake to prevent replay attacks.

The client should print out either `Certificate issued by CA.` or `CA did not issue this certificate!` (as well as everything it prints from the previous parts).

