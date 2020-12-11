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

# Appendex A: Crypto-DSL Reference

## Assignment

```
<name> = <expression>;
valid = validate(..)
```

Assigns the expression on the right hand side to the variable on the left hand side, creating a new variable if valid is undefined, or updating valid if it has already been defined.

## If Statement

```
if <expression> { 
<true_branch> 
} else {
    <false_branch>
}

if not valid {
    print(“invalid”);
} else {
    print(“valid”);
}
```

Evaluates the expression after `if` and executes the first branch if it is `true`, and the second (optional) branch if it is `false`.

## Defining a Function

```
def <fn_name>(<arg1>, <arg2>, ...) {
    <fn_body>
}

def validate(material) {
    return material == 123;
}
```

Defines a function with named arguments that can return a value. Variables defined as `global` in the same file are in scope in `<fn_body>`, as well as any other functions or structs defined in that file.

## Defining a Party

```
party <party_name>(<arg1>, <arg2>, ...) {
    <party_body>
}

party alice() {
    bob.send(“hello”);
}
```

Defines a party that can have named arguments, like a function. Parties are the entrypoints into a protocol, they cannot be called in the protocol code (e.g. `alice();`), instead they must be invoked from the command like `./cdsl party <file_name> <party_name> --id <unique_id>`. The `<unique_id>` is a detail that allows multiple instances of the same protocol to run simultaneously. Parties must run with the same `<unique_id>` to communicate.

## Sending/Receiving

```
party alice() {
    bob.send(“hi”);
}

party bob() {
    print(alice.receive());
}
```

Parties are able to communicate by calling `<party_name>.send(..)` and `.. = <party_name>.receive()`, where `<party_name>` is the name of another party defined in the same file. `send` and `receive` are blocking operations, meaning that a protocol may deadlock, for instance if alice and bob both try to send first, instead of alice sending first, and bob receiving first.

## Tuple Destructuring

```
party alice() {
    ...
    sig = schnorr::sign(sk, (x, y, z));
    bob.send((sig, x, y, z));
}

party bob() {
    ...
    (sig, x, y, z) = alice.receive();
    valid = schnorr::verify(pk, (x, y, z));
}
```

Multiple values can be grouped into a tuple, which is useful if you want to send a message that has multiple values, or generate a signature over those values. In the snippet above, alice uses `(x, y, z)` to group three variables together into a tuple to be signed, and then sends `(sig, x, y, z)` to bob. Bob destructures the tuple with `(sig, x, y, z) = alice.receive();` so that each item in the tuple can be used later in the protocol. 

## Calling an External Function

```
prot foo;
foo::bar();
```

Protocols can be separated into files and imported with the `prot` keyword. Then you can call functions in an external protocol with the syntax `<prot_name>::<fn_name>(..);`

## Structs/Methods/Impl

```
struct Rectangle {
    length,
    width,
}
```

Defines a struct named `Rectangle` that has two named fields `length` and `width`.

```
x = Rectangle {
    length: 10,
    field2 : 20
};
```

Creates an instance of the `Rectangle` struct and assigns it to `x`. Struct fields can be accessed directly (`x_len = x.length;`).

```
impl Foo {
    def area(self) {
        return self.length * self.width;
    }
    def set_len(self, len) {
        Self.len = len;
    }
}
```

Structs can also define methods inside `impl` blocks, then you can call methods (`x_area = x.area();`).
