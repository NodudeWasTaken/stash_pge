# Stash PostgreSQL Perceptual Hash Extension

This project is a PostgreSQL extension to calculate the perceptual hash (phash) distance between two images directly within your database.

This provides a `PhashDistance` function for PostgreSQL.

## Prerequisites

Before you can build and install this extension, you'll need to install a few dependencies.

For Debian/Ubuntu-based systems, you can install them with:
```bash
sudo apt-get update
sudo apt-get install build-essential golang postgresql-server-dev-14
```
*Note: Adjust `postgresql-server-dev-14` to match your PostgreSQL version if you are not using version 14.*

## Installation

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/NodudeWasTaken/stash_pge.git
    cd stash_pge
    ```

2.  **Build and install the extension:**
    Run `make install` to build the extension and install it into your database. You can specify the PostgreSQL version, database name, and user.

    ```bash
    make install
    ```

    For a specific setup, you can provide variables to the make command. For example:
    ```bash
    PGVER=14 DBUSER=user DBNAME=stash make install
    ```

## Usage

Once installed, you can use the `PhashDistance` function in your SQL queries.

**Example:**
```sql
SELECT PhashDistance(1234567890, 9876543210);
```
This will return the perceptual hash distance between the two provided phash values.
