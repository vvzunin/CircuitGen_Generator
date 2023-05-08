import io
import os

from synology_drive_api.drive import SynologyDrive


def upload_to_synology(dataset_id):
    NAS_USER = 'project1290'
    NAS_PASS = '~.*{*$7]NJ1[pS`\\'
    NAS_IP = 'vvzunin.me'
    NAS_PORT = 10003
    dsm_version = '7'

    with SynologyDrive(NAS_USER, NAS_PASS, NAS_IP, NAS_PORT, dsm_version=dsm_version) as synd:
        dataset_id = str(dataset_id)
        dataset_dir = './dataset/' + dataset_id
        for param in os.listdir(dataset_dir):
            param_dir = dataset_dir + '/' + param
            for circuit in os.listdir(param_dir):
                circuit_dir = param_dir + '/' + circuit
                verilog_path = circuit_dir + '/' + circuit + '.v'
                with open(verilog_path, 'rb') as file:
                    bfile = io.BytesIO(file.read())
                    bfile.name = dataset_id + '/' + param + '/' + circuit + '/' + circuit + '.v'
                    synd.upload_file(bfile, dest_folder_path='/team-folders/circuits/')


upload_to_synology('141')
