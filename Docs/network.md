# ORCS Network

## Packet Format
ORCS packets all follow a common format of:
[network key] - 8 characters
[network access group] - 8 characters
[sender mac address] - "XX:XX:XX:XX:XX:XX"
[message contents] - Message text string

## Packet Handling
Packets are handled based on the access group they are sent to.
The public access group is simple text messages does not affect alerts or systems.
The control access group is used for future expansion into controlling individual nodes directly.
The alert access group is used to send alerts. Any message on this access group will cause an already state, including test alerts or any other message.

## Network Band
The network can be run on any LoRa band as long as the usage of the band complies with local regulations. Some limitations may be transmission limits (such as x packets per hour), channel width limits (not exceeding x kHz per channel), or content restrictions (no encryption). Compliance with local regulations allows bands to remain available for similar projects without repercussions or licensing fees.
If possible, the use of a scanner or SDR can help find a channel that is not being used. The demo uses 434MHz as 433MHz has some other activty, and to minimise the risk of interference to both the demo and the other users, a higher channel was selected.

## Limitations
As the network is designed for slow speed low volume paging, then packet rates are heavily limited to 0.1PPS, or one packet every 10 seconds maximum. Additional limitations are packets can only be text messages, and unencrypted, however the codebase can be developed to support binary packets as well as encryption (where allowed by local regulations).