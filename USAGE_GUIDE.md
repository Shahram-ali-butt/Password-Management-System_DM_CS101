# USAGE GUIDE - Password Security Mechanism
### Complete Step-by-Step Instructions

---

## PART 1: GETTING STARTED

### Step 1: Compilation & Execution

### Option 1: Manual Compilation & Execution

**Compilation:**
```bash
g++ -o main main.cpp crypto_functions.cpp
```

**Running Program:**
```bash
./main
```

### Option 2: Running Bash Script
```bash
./build.sh
```

---

## PART 2: USING THE PROGRAM

### Interactive Menu Options:

#### Option 1: Encrypt Password (Caesar)
```
Example:
Enter password: HelloWorld
Enter shift: 3
Output: KhoorZruog
```

**How it works:**
- Each letter is shifted by 3 positions in the alphabet
- H → K, e → h, l → o, etc.
- Mathematical formula: E(x) = (x + 3) mod 26

#### Option 2: Encrypt Password (Vigenère)
```
Example:
Enter password: HelloWorld
Enter key: KEY
Output: RijvsUyvjn
```

**How it works:**
- Each letter is shifted by corresponding key letter
- H + K, e + E, l + Y, etc.
- More secure than Caesar cipher

#### Option 3: Encrypt Password (Affine)
```
Example:
Enter password: HelloWorld
Enter key 'a': 5
Enter key 'b': 8
Output: RcllaOaplx
```

**How it works:**
- Uses formula: E(x) = (5*x + 8) mod 26
- Key 'a' must be coprime with 26
- Valid values for 'a': 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25

#### Option 4: Hash Password
```
Example:
Enter password: MyPassword123
Output: 972352
```

**How it works:**
- One-way function - cannot be reversed
- Same password always produces same hash
- Used for secure password storage

#### Option 5: Join Two Ciphers
```
Example:
Enter your combination (12, 13 or 23): 13
Enter password to encrypt: HelloWorld
Enter shift value (1-25): 3
Caesar Encrypted password: KhoorZruog
Enter key 'a' (must be coprime with 26): 5
Enter key 'b': 8
Final Encrypted password: GraapDpeam
```

**How it works:**
- Encripts password using one cipher
- Uses the encripted cipher text as input for the second cipher
- Provides extra security


#### Option 6: Run All Demonstrations
- Automatically runs demos of all encryption methods
- Shows Caesar, Vigenère, Affine, and Hash
- Great for presentations

#### Option 6: Get Explanations
- Buit-in explanations of all encryption methods
- Explains Caesar, Vigenère, Affine, and Hash


## PART 3: CHOOSING ENCRYPTION METHOD

### When to Use Each Method:

**1. Caesar Cipher:**
- **Use for:** Learning purposes, simple demonstrations
- **Security:** LOW
- **Speed:** VERY FAST
- **Best for:** Non-critical data, educational projects

**2. Vigenère Cipher:**
- **Use for:** Medium security needs
- **Security:** MEDIUM
- **Speed:** FAST
- **Best for:** Student projects, hobby applications

**3. Affine Cipher:**
- **Use for:** Demonstrating modular arithmetic
- **Security:** LOW-MEDIUM
- **Speed:** FAST
- **Best for:** Educational purposes, math demonstrations

**4. Hash Function:**
- **Use for:** Password verification (RECOMMENDED)
- **Security:** BETTER
- **Speed:** VERY FAST
- **Best for:** Login systems, authentication
- **Note:** Cannot retrieve original password

### Conclusion:

✓ **Before:** Passwords stored in plain text (INSECURE)
✓ **After:** Passwords encrypted using discrete math (SECURE)
✓ **Concepts:** Modular arithmetic, number theory, cryptography
✓ **Real-world:** How actual systems protect passwords
✓ **Learning:** Connection between math theory and CS practice

---

