/*----------------------------------------------------------------------------------------------------------------
Version:	AdoAssist 1.20
   Time:	2012-05-12 15:25:14
    SQL:	SELECT * FROM tbl_Demo
----------------------------------------------------------------------------------------------------------------*/
using System;
//using System.Collections.Generic;
//using System.Text;

namespace Database
{
	public class DBClassName : Database.IDBOperability
	{
        #region Data and Attr

				/// <summary>
        /// 0 ID adInteger
        /// </summary>
        protected long m_lID;

        /// <summary>
        /// 0 ID adInteger
        /// </summary>
        public long m_lID
        {
            get
            {
                return m_lID;
            }
            set
            {
                m_lID = value;
            }
        }
	
		/// <summary>
        /// 1 Guid adVarWChar
        /// </summary>
        protected CString m_strGuid;

        /// <summary>
        /// 1 Guid adVarWChar
        /// </summary>
        public CString m_strGuid
        {
            get
            {
                return m_strGuid;
            }
            set
            {
                m_strGuid = value;
            }
        }
	
		/// <summary>
        /// 2 Name adVarWChar
        /// </summary>
        protected CString m_strName;

        /// <summary>
        /// 2 Name adVarWChar
        /// </summary>
        public CString m_strName
        {
            get
            {
                return m_strName;
            }
            set
            {
                m_strName = value;
            }
        }
	
		/// <summary>
        /// 3 Age adInteger
        /// </summary>
        protected long m_lAge;

        /// <summary>
        /// 3 Age adInteger
        /// </summary>
        public long m_lAge
        {
            get
            {
                return m_lAge;
            }
            set
            {
                m_lAge = value;
            }
        }
	


        #endregion

        #region IDBOperability

        public void DBSetData(System.Data.DataRow datarow, ulong nFlag)
        {
            var x = datarow;
			//			x["ID"] = ID;
			x["Guid"] = Guid;
			x["Name"] = Name;
			x["Age"] = Age;

	/*
//			x[0] = ID;
			x[1] = Guid;
			x[2] = Name;
			x[3] = Age;
	*/

        }

        public void DBGetData(System.Data.IDataReader reader, ulong nFlag)
        {
            var x = reader;
						DBConvert.Convert(out m_lID, x["ID"]);
			DBConvert.Convert(out m_strGuid, x["Guid"]);
			DBConvert.Convert(out m_strName, x["Name"]);
			DBConvert.Convert(out m_lAge, x["Age"]);

	/*
			DBConvert.Convert(out 0, x[ID]);
			DBConvert.Convert(out 1, x[Guid]);
			DBConvert.Convert(out 2, x[Name]);
			DBConvert.Convert(out 3, x[Age]);
	*/

        }

        #endregion
    }
}
