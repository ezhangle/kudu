// Copyright (c) 2014, Cloudera, inc.
package kudu.rpc;

public class CreateTableResponse extends KuduRpcResponse {

  /**
   * @param ellapsedMillis Time in milliseconds since RPC creation to now.
   */
  CreateTableResponse(long ellapsedMillis) {
    super(ellapsedMillis);
  }
}