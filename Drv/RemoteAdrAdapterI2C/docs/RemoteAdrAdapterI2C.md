<title>RemoteAdrAdapterI2C Component Dictionary</title>
# RemoteAdrAdapterI2C Component Dictionary


## Telemetry Channel List

|Channel Name|ID|Type|Description|
|---|---|---|---|
|REMADR_Reads|0 (0x0)|U32|Bytes Sent|
|REMADR_Writes|1 (0x1)|U32|Bytes Received|

## Event List

|Event Name|ID|Description|Arg Name|Arg Type|Arg Size|Description
|---|---|---|---|---|---|---|
|REMADR_FailedTransaction|0 (0x0)|UART open error| | | | |
| | | |error|U16||I2C address|    
|REMADR_ShortTransaction|1 (0x1)|UART open error| | | | |
| | | |error|U16||I2C address|    
|REMADR_Read|2 (0x2)|Requested to read from an address| | | | |
| | | |i2caddress|U8||I2C address|    
| | | |registeraddress|U8||reg address|    
| | | |value|U8||value|    
|REMADR_Write|3 (0x3)|Requested to read from an address| | | | |
| | | |i2caddress|U8||I2C address|    
| | | |registeraddress|U8||reg address|    
| | | |value|U8||value|    
