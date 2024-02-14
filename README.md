# WhiteRabbit-EEPROM-SFP
How to bypass the EEPROM checksum when a header is corrupted


Sometimes, the SFP Glenair may have problems with the shared memory of the EEPROM, a header of 96 byte of simples informations like Vendor Id, Serial, Date production,
that you can always rewrite throught I2C Bus. When one of thus data is corrupted for some reason, the checksum fails and the diagnostic is turned off!
To recovery the funtionality we need to rewrite the header and this script do this in every scenario, also when some bytes can't be rewritable.
