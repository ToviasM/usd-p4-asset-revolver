
# POC USD P4 Asset Resolver

P4 USD Asset Resolver is a proof of concept (POC) designed to facilitate integration of Perforce with Pixar's Universal Scene Description (USD) framework. This tool resolves USD reference paths that reference stream paths of assets stored in Perforce.

This project can be expanded into larger production pipelines with features like caching, asset pinning, and timestamp validation to ensure efficient asset handling and retrieval.
## Building Locally

### 1. Clone the Project

First, clone the repository:

```bash
  git clone https://github.com/ToviasM/usd-p4-asset-resolver.git
```

### 2. Installing Dependencies 

Next, create a directory within the cloned project for dependencies:
```
mkdir dependencies
```

Download the following libraries and place them in the dependencies folder. Please ensure you use Perforce's dynamic libraries:

- [p4api_vs2022_dyn_openssl1.1.1.zip](https://ftp.perforce.com/perforce/r24.1/bin.ntx64/p4api_vs2022_dyn_openssl1.1.1.zip)
- [openssl-1.1.1w.zip](https://download.firedaemon.com/FireDaemon-OpenSSL/openssl-1.1.1w.zip)

Your folder structure should look like this:

```bash
    usd-p4-asset-resolver/dependencies/P4/lib/p4api.lib
    usd-p4-asset-resolver/dependencies/openssl/lib/openSSL.lib
```

### 3. Building Against Your USD Library
To build the project, it must be linked to your desired DCC’s USD library. Edit the build.bat script to specify the path to your DCC. Currently, the project supports Maya and Houdini.

In build.bat, update the HFS variable to point to your DCC installation, for example:
```
set HFS=D:/SideFX/Houdini20.5.332
```

### 4. Installation
Run the build script to compile the project:
```bash
  build.bat
```

After running the build script, confirm that the project has been successfully built by checking the ```dist``` directory.

### 5. SSL DLLs
Ensure that the OpenSLL dlls have been included in the installed plugins directory. Otherwise, the DLL will fail to load. 

## Pipeline FAQ

#### Why Use Perforce for Asset Resolution?

Integrating Perforce at the asset level introduces several challenges and should only be implemented under specific circumstances. In this case, it's used for referencing P4 paths that reside outside the project’s directory.

It also allows us to maintain a source control API that can be referenced in other DCCS. For example, syncing assets, submitting, and validating. 

#### Isn't This a Heavy Load for the CPU?

Yes, it is! This approach should ideally be implemented within a larger pipeline that includes caching and pinning mechanisms to manage assets that have already been pulled. You can also check timestamps to validate the age of assets. For simplicity, I chose to exclude these features from the repository.



## References 

- [Basic USD Asset Resolver](https://github.com/charlesfleche/arHttp)
- [Caching and Pinning](https://github.com/LucaScheller/VFX-UsdAssetResolver)
- [P4 API Reference](https://ftp.perforce.com/perforce/r24.1/bin.ntx64/)
