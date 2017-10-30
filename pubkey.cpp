#include <iostream>
#include <bitcoin/bitcoin.hpp>

std::string pubkey(const std::string &secret_key) ;

int main() {
    std::string secret = std::to_string(bc::pseudo_random());
    std::cout << "Secret: ";
    std::cout << secret;
    std::cout << "\nPublic: ";
    std::cout << pubkey(secret);
    std::cout << "\n";

    return 0;
}

std::string pubkey(const std::string &secret_key) {
    // Private secret key.
    bc::ec_secret secret{};
    bc::decode_base16(secret, secret_key);

    // Get public key.
    bc::ec_compressed public_key{};
    bc::secret_to_public(public_key, secret);

    // Create Bitcoin address.
    // Normally you can use:
    // bc::payment_address payaddr;
    // bc::set_public_key(payaddr, public_key);
    // const std::string address = payaddr.encoded();
    // Compute hash of public key for P2PKH address.
    const bc::short_hash hash = bc::bitcoin_short_hash(public_key);
    bc::data_chunk unencoded_address;

    // Reserve 25 bytes
    // [ version:1 ]
    // [ hash:20 ]
    // [ checksum:4 ]
    unencoded_address.reserve(25);
    // Version byte, 0 is normal BTC address (P2PKH).
    unencoded_address.push_back(0);
    // Hash data
    bc::extend_data(unencoded_address, hash);
    // Checksum is computed by hashing data, and adding 4 bytes from hash.
    bc::append_checksum(unencoded_address);
    // Finally we must encode the result in Bitcoin's base58 encoding
    assert(unencoded_address.size() == 25);
    const std::string address = bc::encode_base58(unencoded_address);

    return address;
}