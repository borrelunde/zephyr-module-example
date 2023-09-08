# Zephyr Module Template

This is a template that lets you get going with Zephyr module development quickly.

Not all features of a module is included in this repository.

## Getting Started

Run Command Prompt.

Go to the directory where you would like your Zephyr module project to be.

```shell
cd <path\to\zephyr-projects>
```

Create a new virtual environment.

```shell
python -m venv zephyr-module-project\.venv
```

Activate the virtual environment.

```shell
zephyr-module-project\.venv\Scripts\activate.bat
```

Once activated your shell will be prefixed with `(.venv)`. The virtual environment can be deactivated at any time by running `deactivate`.

Install west.

```shell
pip install west
```

Initialize the workspace and get the Zephyr source code.

```shell
west init -m https://github.com/borrelunde/zephyr-module --mr master zephyr-module-project
cd zephyr-module-project
west update
```

Enter the application directory.

```shell
cd zephyr-module
```

## Initial set-up

There are a few steps required before the module can be used.

1. `Kconfig` needs to configure the library support option. Simply uncomment the comments and replace `MODULE_NAME` with the actual module name.

   ```
   config MODULE_EXAMPLE
   	bool "Module example support"
   	default n
   	help
   		This option enables module example.
   ```

2. `CMakeLists.txt` is configured for a simple module, it might need to be expanded upon later.

3. `west.yml` does not need to be changed, however, it is considered good practice to set the self path.

   ```yml
   manifest:
     version: 0.7

     self:
       # Where this repository should be cloned to.
       path: module-example
   ```

4. `zephyr/module.yml` is configured without pointing to the dts root directory nor the board root directory, this can be added like so.

   ```yml
   build:
     # ...
     settings:
       # Additional roots for boards and DTS files. Zephyr will use the
       # `<board_root>/boards` for additional boards. The `.` is the root of this
       # repository.
       board_root: .
       # Zephyr will use the `<dts_root>/dts` for additional dts files and
       # `<dts_root>/dts/bindings` for additional dts binding files. The `.` is
       # the root of this repository.
       dts_root: .
   ```

## Add module to an application

Add the module as an entry in an application's `west.yml` file.

```yml
- name: <module>
  url: https://github.com/<user>/<module>
  revision: <branch>
  path: modules/<module>
  # consider import: true
```

Below is an example application's `west.yml` file.

```yml
manifest:
  version: 0.7

  self:
    west-commands: scripts/west-commands.yml

  remotes:
    - name: zephyrproject-rtos
      url-base: https://github.com/zephyrproject-rtos
    - name: remote-example
      url-base: https://github.com/user-example

  projects:
    - name: zephyr
      remote: zephyrproject-rtos
      revision: main
      import:
        name-allowlist:
          - cmsis # required by the ARM port
          - hal_nordic # required by the nrf52840dk board (Nordic based)

    - name: module-example # this should be the name of the module repository on GitHub
      path: modules/module-example # the path is configurable to your liking
      remote: remote-example # remote is used instead of url, the remote is defined above projects
      revision: main # you can choose which branch to use, the names must match
```

Use `west update` to download the module to your application.

Having entered the entry, West can list the module with the command `west list`.

```
manifest     zephyr-application           HEAD                                     N/A
zephyr       zephyr                       main                                     https://github.com/zephyrproject-rtos/zephyr
<module>     <path>                       <branch>                                 https://github.com/<user>/<module>
...			 ...						  ...									   ...
```
