// NOTE:- 2 hex data or num = 1 byte 

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

int main()
{
    /* plaintext */
    unsigned char plaintext[30];// = "Hello OpenSSL AES Encryption";

	printf("Enter the data..\n");
	scanf("%[^\n]",plaintext);

    /* key = 32 bytes (256 bits) */
    unsigned char key[32] = "01234567890123456789012345678901";

    /* iv = 16 bytes */
    unsigned char iv[16] = "0123456789012345";


   // RAND_bytes(key,sizeof(key));
   // RAND_bytes(iv,sizeof(iv));
    
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    int len;
    int ciphertext_len;
    int decrypted_len;

    EVP_CIPHER_CTX *ctx;

    /* ========================= */
    /* ENCRYPTION PART */
    /* ========================= */

    ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, strlen((char*)plaintext));
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    printf("Ciphertext (hex): ");
    for(int i = 0; i < ciphertext_len; i++)
        printf("%02x ", ciphertext[i]);
    printf("\n");

    /* ========================= */
    /* DECRYPTION PART */
    /* ========================= */

    ctx = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len);
    decrypted_len = len;

    EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len);
    decrypted_len += len;

    EVP_CIPHER_CTX_free(ctx);

    decryptedtext[decrypted_len] = '\0';

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
