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


## PART 3: BUSINESS APPLICATION INTEGRATION

### Overview
The passwordManagement.cpp file provides complete encryption for a business inventory management system, securing both usernames and passwords using multiple encryption techniques.

### Implementation in Existing Application

#### Step 1: Include the Header
```cpp
#include "crypto_functions.h"
```

#### Step 2: Set Up File Constants
```cpp
const string userFile = "users.txt";
const string signUpFile = "signUpData.txt";
const string adminFile = "admin.txt";
```

#### Step 3: Store User Data Securely
```cpp
// Encrypt and store user data
int currentUsers = 3;
string userNames[] = {"John Doe", "Jane Smith", "Bob Wilson"};
string userPasswords[] = {"hash123", "hash456", "hash789"};

storeUserDataEnc(currentUsers, userNames, userPasswords);
// Users are now stored with encrypted usernames and hashed passwords
```

**What happens:**
- Spaces in usernames are replaced with 'X' (e.g., "John Doe" → "JohnXDoe")
- Usernames are encrypted using Affine cipher (a=5, b=8)
- Passwords are already hashed before this function
- Data is stored in format: `encryptedUsername,hashedPassword`

#### Step 4: Verify User Login
```cpp
string currentUser;
string username = "John Doe";
string password = "userPassword123";

if (verifyUser(currentUser, username, password)) {
    cout << "Welcome back, " << currentUser << "!" << endl;
    // Proceed to application
} else {
    cout << "Invalid credentials!" << endl;
}
```

**What happens:**
- Password is hashed automatically
- File is searched for matching encrypted username
- Username is decrypted and spaces are restored
- Hashed passwords are compared
- If match found, `currentUser` contains the decrypted username

#### Step 5: Admin Authentication
```cpp
string adminPassword = "AdminSecure@2025";

if (verifyAdmin(adminPassword)) {
    cout << "Admin access granted" << endl;
    // Show admin panel
} else {
    cout << "Admin authentication failed" << endl;
}
```

**What happens:**
- Password is double-hashed: `hash(hash(password))`
- Provides extra security layer for admin account
- Compared with stored double-hash in admin.txt

#### Step 6: Handle Signup Requests
```cpp
// Store signup request (encrypted separately from regular users)
int signUpRequests = 2;
string signUpRequestData[100][2];
signUpRequestData[0][0] = "New User";
signUpRequestData[0][1] = "hash123";
signUpRequestData[1][0] = "Another User";
signUpRequestData[1][1] = "hash456";

storeSignUpDataEnc(signUpRequests, signUpRequestData);

// Later, admin loads and reviews signup requests
loadSignUpDataDec(signUpRequests, signUpRequestData);
for(int i = 0; i < signUpRequests; i++) {
    cout << "Signup Request: " << signUpRequestData[i][0] << endl;
    // Admin can approve or reject
}
```

**What happens:**
- Signup requests use different Affine keys (a=9, b=15)
- Keeps signup data separate from active users
- Admin can decrypt and review before approving

#### Step 7: Check Username Availability
```cpp
string newUsername = "John Doe";

if (checkUserExists(newUsername)) {
    cout << "Username already taken. Please choose another." << endl;
} else {
    cout << "Username available!" << endl;
    // Proceed with registration
}
```

**What happens:**
- Searches encrypted data without exposing plain text
- Decrypts each stored username temporarily for comparison
- Returns true if username exists, false otherwise

### Complete Registration Flow Example

```cpp
// User Registration Function
bool registerNewUser(string username, string password) {
    // Step 1: Check if username exists
    if (checkUserExists(username)) {
        cout << "Username already exists!" << endl;
        return false;
    }
    
    // Step 2: Hash the password
    string hashedPassword = hashPassword(password);
    
    // Step 3: Add to signup requests
    int signUpRequests;
    string signUpRequestData[100][2];
    
    // Load existing requests
    loadSignUpDataDec(signUpRequests, signUpRequestData);
    
    // Add new request
    signUpRequestData[signUpRequests][0] = username;
    signUpRequestData[signUpRequests][1] = hashedPassword;
    signUpRequests++;
    
    // Save encrypted signup data
    storeSignUpDataEnc(signUpRequests, signUpRequestData);
    
    cout << "Registration request submitted!" << endl;
    return true;
}

// Admin Approval Function
void approveSignup(int requestIndex) {
    int signUpRequests, currentUsers;
    string signUpRequestData[100][2];
    string userNames[100], userPasswords[100];
    
    // Load signup requests
    loadSignUpDataDec(signUpRequests, signUpRequestData);
    
    // Load current users
    loadUserDataDec(currentUsers, userNames, userPasswords);
    
    // Move approved user to main users
    userNames[currentUsers] = signUpRequestData[requestIndex][0];
    userPasswords[currentUsers] = signUpRequestData[requestIndex][1];
    currentUsers++;
    
    // Remove from signup requests
    for(int i = requestIndex; i < signUpRequests - 1; i++) {
        signUpRequestData[i][0] = signUpRequestData[i+1][0];
        signUpRequestData[i][1] = signUpRequestData[i+1][1];
    }
    signUpRequests--;
    
    // Save updated data
    storeUserDataEnc(currentUsers, userNames, userPasswords);
    storeSignUpDataEnc(signUpRequests, signUpRequestData);
    
    cout << "User approved successfully!" << endl;
}
```

### Security Best Practices

1. **Always Hash Before Storage**: Hash passwords before calling `storeUserDataEnc()`
2. **Different Keys for Different Data**: Signup requests use different keys than regular users
3. **Admin Extra Protection**: Double-hash admin passwords
4. **Never Store Plain Text**: All data is encrypted before writing to files
5. **Handle Spaces Properly**: System automatically handles spaces in usernames

### File Format Reference

**users.txt Format:**
```
<number_of_users>
<encrypted_username>,<hashed_password>
<encrypted_username>,<hashed_password>
...
```

**Example:**
```
3
RcllaOaplx,972352
Pcala,876543
Pcalancrclqh,765432
```

**signUpData.txt Format:**
```
<number_of_requests>
<encrypted_username>,<hashed_password>
<encrypted_username>,<hashed_password>
...
```

**admin.txt Format:**
```
<double_hashed_admin_password>
```

### Troubleshooting

**Problem: Verification fails with correct password**
- Ensure password was hashed before storage
- Check that the correct encryption method is used
- Verify file format is correct

**Problem: Usernames with spaces not working**
- System automatically handles spaces (converts to 'X')
- Ensure you're not manually modifying encrypted data

**Problem: Admin login not working**
- Remember admin password is double-hashed
- Check admin.txt contains the correct double-hash

---

## PART 4: CHOOSING ENCRYPTION METHOD

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

