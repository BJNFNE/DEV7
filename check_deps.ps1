# Function to log debug info to console
function print_debug_info {
    param([string]$info)
    Write-Output "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') - $info"
}

# Check for the presence of required commands or utilities
function check_command {
    param([string]$cmd, [string]$desc)
    if (Get-Command $cmd -ErrorAction SilentlyContinue) {
        print_debug_info "$desc found at $((Get-Command $cmd).Source)"
    } else {
        print_debug_info "$desc is required but not found. - Not installed"
        return 1
    }
}

# Check for the presence of Visual Studio folder on hard drives
function check_visual_studio {
    $vs_installed = $false
    $driveLetters = "C", "D", "E"
    $vs_folder_name = "Microsoft Visual Studio"
    
    foreach ($drive in $driveLetters) {
        $vs_path = "${drive}:\Program Files (x86)\$vs_folder_name"
        if (Test-Path $vs_path) {
            $vs_installed = $true
            print_debug_info "Visual Studio found at $vs_path"
            break
        }
    }

    # Check for the presence of Python3 folder on hard drives
function check_python3 {
    $python3_installed = $false
    $driveLetters = "C", "D", "E"
    $python3_folder_name = "Python3"
    
    foreach ($drive in $driveLetters) {
        $vs_path = "${drive}:\Program Files (x86)\$python3_folder_name"
        if (Test-Path $python3_path) {
            $python3_installed = $true
            print_debug_info "Python3 found at $python3_path"
            break
        }
    }

    if (-not $vs_installed) {
        print_debug_info "Visual Studio is required but not found. - Not installed"
        return 1
    else if (-not $python3_installed) {
        print_debug_info "Python3 is required but not found. - Not installed"
    }
    
    }

    return 0
}

Write-Output "Checking your system..."

# Check for the presence of essential commands
check_command "python" "Python 3"

# Check for the presence of Visual Studio folder
check_visual_studio

Write-Output "Checking complete. You can now compile DEV7 Tools."
