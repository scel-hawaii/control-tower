import copy
import json
import datetime


def serialize_frame(f):
    """
    Converts a frame object to json
    """
    f_copy = copy.copy(f)
    f_copy["source_addr_long"] = f_copy["source_addr_long"].hex()
    f_copy["source_addr"] = f_copy["source_addr"].hex()
    f_copy["rf_data"] = f_copy["rf_data"].hex()
    f_copy["options"] = f_copy["options"].hex()
    f_copy["time_recieved"] = str(datetime.datetime.now())
    return json.dumps(f_copy)
