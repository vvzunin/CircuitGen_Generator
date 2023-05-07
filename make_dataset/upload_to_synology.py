from synology_drive_api.drive import SynologyDrive


def upload_to_synology():

    NAS_USER = 'project1290'
    NAS_PASS = '~.*{*$7]NJ1[pS`\\'
    NAS_IP = 'vvzunin.me'
    NAS_PORT = 10003
    dsm_version = '7'

    with SynologyDrive(NAS_USER, NAS_PASS, NAS_IP, NAS_PORT, dsm_version=dsm_version) as synd:
        a = synd.list_folder('/team-folders/circuits')  # Папка circuits
        items = a['data']['items']
        for i in items:
            print(i['name'])
        pass